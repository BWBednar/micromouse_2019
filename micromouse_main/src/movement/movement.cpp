/* movement.cpp 
 * 
 * This file is used to calculate the speed to set the motors at to get closer to the next location
 * 
 * Model:
 * C: current_location - the current state of the robot
 * N: next_location - goal location, where we want to be
 * I: intermediate_location - Not always used, but the location we should travel to first before attempting to go to the next_location
 * v and ->: path of robot, goes down then over because the error in x is less than the error in y
 * 
 * Axis Definition:
 * +--> +X                                      N.x                                  
 * |                                             |                            
 * V        C                                    |                             
 * +Y       v                                    |                            
 *          v                                    |                           
 *          v                                    |                           
 *   - - - -v- - - - - - - - - - - - - - - - - - | - - - -
 *          v                                    |       ^
 *          v                                    |       TOLERANCE_MM
 *          v                                    |       v
 *  --------I->->->->->->->->->->->->->->->->->->N-------- N.y               
 *                                               |       ^
 *                                               |       TOLERANCE_MM
 *                                               |       v
 *   - - - - - - - - - - - - - - - - - - - - - - | - - - -
 * 
 * Main ideas:
 * - Get to a point where you are within the goal tolerance for one axis before try to drive there
 * - Either call straightController() or turnController() each time based on what state we are determined to be in
 * - Once within tolerance for both x and y stop motors completely
 * 
 * */


#include "movement.h"
#include "../types.h"
#include "../abs.h"
//#include <stdlib.h>


#define IS_BETWEEN_ERROR(x,y,e) (((x) < (y) + (e)) && ((x) > (y) - (e)))

// Globals
enum RobotState {
    PERFECT,                    // Within tolerance for both x and y
    OUT_XY_IN_THETA,            // Outside tolerance for one of x and y AND within tolerance for Theta
    OUT_XY_OUT_THETA,           // Outside tolerance for one of x and y AND outside tolerance for Theta
    IN_XY_IN_THETA,             // Within tolerance for one of x and y AND within tolerance for Theta
    IN_XY_OUT_THETA             // Within tolerance for one of x and y AND outside tolerance for Theta
};

enum Direction {
    North,  // North(0, -1) theta = 3*PI/2
    East,   // East(1, 0)   theta = 0
    South,  // South(0, 1)  theta = PI/2
    West,   // West(-1, 0)  theta = PI
};

double directionToRAD[4] = { 3*PI/2, 0, PI/2, PI };

double directionToXY[4][2] = { { 0, -1 }, { 1, 0 }, { 1, 0 }, { -1, 0 } };

gaussian_location_t prev_location;


// Function Declarations


/*----------- Public Functions -----------*/

void initializeMovement(gaussian_location_t* current_location) {
    prev_location = *current_location;
}

/* calculate speed
 * Calculate the speed to set the motors to given the current_location and the next_location
 * - left_speed and right_speed should be passed in with the current respective speeds*/
void calculateSpeed(gaussian_location_t* current_location, gaussian_location_t* next_location,
                        double* left_speed, double* right_speed) {
    
    // Overall changes
    double x_cte = next_location->x_mu - current_location->x_mu;
    double y_cte = next_location->y_mu - current_location->y_mu;

    RobotState currentState;
    Direction direction;
    
    if (abs(x_cte) > TOLERANCE_MM && abs(y_cte) > TOLERANCE_MM) {
        
        // Determine the direction to go
        direction = chooseDirectionOutOfTolerance(x_cte, y_cte);

        // Are we facing that direction?
        if (IS_BETWEEN_ERROR(current_location->theta_mu, directionToRAD[direction], TOLERANCE_RAD)) {
            currentState = OUT_XY_IN_THETA;
        } else {
            currentState = OUT_XY_OUT_THETA;
        }

    } else if (abs(x_cte) < TOLERANCE_MM && abs(y_cte) < TOLERANCE_MM) {
        
        currentState = PERFECT;

    } else {

        // Determine the direction to go
        direction = chooseDirectionWithinTolerance(x_cte, y_cte);

        // Are we facing that direction?
        if (IS_BETWEEN_ERROR(current_location->theta_mu, directionToRAD[direction], TOLERANCE_RAD)) {
            currentState = IN_XY_IN_THETA;
        } else {
            currentState = IN_XY_OUT_THETA;
        }
    }

    switch (currentState) {
        case PERFECT:
            // Stop
            *left_speed = 0;
            *right_speed = 0;
            break;
        case OUT_XY_IN_THETA:
            // Go Straight to get to within the tolerance

            // We need to find the location that is on the same axis as the next_location
            // in the direction we are being told to go
            gaussian_location_t intermediate_location;
            
            // Direction does not depend on x, set to stay the same as previous location to keep same axis for cte
            if (directionToXY[direction][0] == 0)
                intermediate_location.x_mu = prev_location.x_mu;
            else // Direction does depend on x, project to axis by setting to next location
                intermediate_location.x_mu = next_location->x_mu;

            // Direction does not depend on y, set to stay the same as previous location to keep same axis for cte
            if (directionToXY[direction][1] == 0)
                intermediate_location.y_mu = prev_location.y_mu;
            else // Direction does depend on y, project to axis by setting to next location
                intermediate_location.y_mu = next_location->y_mu;

            straightController(current_location, &intermediate_location, left_speed, right_speed, direction);
            break;

        case OUT_XY_OUT_THETA:
            // Turn to get to within the tolerance of direction
            turnController(current_location, left_speed, right_speed, direction);
            break;
        case IN_XY_IN_THETA:
            // Go Straight
            straightController(current_location, next_location, left_speed, right_speed, direction);
            break;
        case IN_XY_OUT_THETA:
            // Turn to get to within the tolerance of direction
            turnController(current_location, left_speed, right_speed, direction);
            break;
    }

    prev_location = *current_location;
}

Direction chooseDirectionOutOfTolerance(double x_cte, double y_cte) {
    if (abs(x_cte) < abs(y_cte)) 
        return x_cte > 0 ? East : West;
    else
        return y_cte > 0 ? South : North;
}

Direction chooseDirectionWithinTolerance(double x_cte, double y_cte) {
    if (abs(x_cte) < abs(y_cte)) 
        return y_cte > 0 ? South : North;
    else
        return x_cte > 0 ? East : West;
}

void straightController(gaussian_location_t* current_location, gaussian_location_t* next_location,
                            double* left_speed, double* right_speed, Direction dir) {
    

}

void turnController(gaussian_location_t* current_location, double* left_speed, double* right_speed, Direction dir) {

}
