/* settings.h */

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "link_Arduino.h"


// General
#define DEBUG false

// Main
#define MAIN_LOOP_TIME 10000    // Delay between the start of each main_loop call in microseconds

// Maze Specifications
#define MAZE_SIZE       16          // If square, the length each side of the maze
#define MAZE_WIDTH      MAZE_SIZE   // Number of cells wide
#define MAZE_HEIGHT     MAZE_SIZE   // Number of cells tall
#define WALL_THICKNESS  12          // Thickness of the walls in mm
#define CELL_LENGTH     168         // Length and width of each cell inside the walls in mm

// Robot
#define WHEEL_RADIUS            16          // Wheel radius in mm
#define TICKS_PER_REVOLUTION    1808.3333   // Number to encoder ticks per one revolution of a wheel
#define WHEEL_BASE_LENGTH       99.5         //dummy value (in mm)

// Localization
#define INIT_X_MU           84.0    //dummy value (in mm)
#define INIT_X_SIGMA        10.0    //dummy value (in mm)
#define INIT_XY_SIGMA       0       //dummy value (in mm)
#define INIT_Y_MU           84.0    //dummy value (in mm)
#define INIT_Y_SIGMA        10.0    //dummy value (in mm)
#define INIT_THETA_MU       0.0     //dummy value (in mm)
#define INIT_THETA_SIGMA    10.0    //dummy value (in mm)

#define ENCODER_VARIANCE_BASE   2.0
#define ENCODER_VARIANCE_PER_MM 0.2

#define X_VARIANCE      1   //dummy value
#define Y_VARIANCE      1   //dummy value
#define THETA_VARIANCE  1   //dummy value

#define TOO_FAR_DISTANCE    125.0   // the distance that of walls that we update given a TOO_FAR measurement (in mm)
#define TOO_CLOSE_DISTANCE  5.0     // the distance that of walls that we update given a TOO_CLOSE measurement (in mm)

#define WALL_HIT_THRESHOLD  10      // The plus or minus amount for a measurement that should result in the increase of a walls exists
#define WALL_UPDATE_AMOUNT  0.05    // The amount to increase or decrease a wall's probability of existing
#define WALL_UPDATE         0.9     // The amount to multiply by to increase or decrease a wall's probability of existing

#define SENSOR_LOCATION_WEIGHT 0.1  // The higher this value, the more we trust our sensor's input

// Strategy
#define INIT_CELL_X     0       // Initial Cell x coordinate
#define INIT_CELL_Y     0       // Initial Cell y coordinate
#define GOAL_CELL_X     7       // Goal cell x coordinate
#define GOAL_CELL_Y     7       // Goal cell y coordinate
#define WALL_THRESHOLD  0.5     // Probability that we believe that a wall actually exists
#define MAX_VALUE       999     // Maximum value that can be in values

// Movement
#define INNER_TOLERANCE_MM    3             //dummy value (in mm)
#define INNER_TOLERANCE_RAD   radians(3)    //dummy value (in radians)
#define OUTER_TOLERANCE_MM    10            //dummy value (in mm)
#define OUTER_TOLERANCE_RAD   radians(10)   //dummy value (in radians)

#define STRAIGHT_TAU_P  5                   // dummy value
#define STRAIGHT_TAU_I  0                   // dummy value
#define STRAIGHT_TAU_D  0.5                 // dummy value
#define STRAIGHT_PROFILE_STABLE_SPEED  100  // dummy value
#define STRAIGHT_PROFILE_SLOPE         5    // dummy value
#define STRAIGHT_PROFILE_INTERCEPT     0    // dummy value

#define TURN_TAU_P      0                   // unused
#define TURN_TAU_I      0                   // unused
#define TURN_TAU_D      0                   // unused
#define TURN_PROFILE_STABLE_SPEED  100
#define TURN_PROFILE_SLOPE         500
#define TURN_PROFILE_INTERCEPT     10

// Control
#define CONTROL_LOOP_TIME   10000   // Delay between start times of control loop in microseconds
#define MOTOR_TAU_P         0.015   // Proportional Gain
#define MOTOR_TAU_I         0.001   // Integral Gain
#define INT_BOUND           500     // Integral Bound
#define MAX_SPEED           250     // Maximum possible speed
#define MIN_SPEED           50      // Minimum possible speed

// Encoders
#define LEFT_ENCODER_PIN_A  49
#define LEFT_ENCODER_PIN_B  48
#define RIGHT_ENCODER_PIN_A 38
#define RIGHT_ENCODER_PIN_B 40

// Motors
#define LEFT    0
#define RIGHT   1
#define RESOLUTION_BITS     8       // Number of bits to use in analogWrite()
#define MAX_PWM_OUTPUT      255     // Should be 2^(RESOLUTION_BITS) - 1
#define MIN_PWM_OUTPUT      50      // Lowest PWM value that the motors can handle
#define LEFT_MOTOR_PIN_A    13
#define LEFT_MOTOR_PIN_B    12
#define RIGHT_MOTOR_PIN_A   5
#define RIGHT_MOTOR_PIN_B   6

// Sensors
#define I2C_RESET_PIN   31
#define TCAADDR         0x70
#define NUM_SENSORS     5
#define SENSOR_0_ADDR   0x00
#define SENSOR_0_PIN    22
#define SENSOR_1_ADDR   0x01
#define SENSOR_1_PIN    33
#define SENSOR_2_ADDR   0x02
#define SENSOR_2_PIN    41
#define SENSOR_3_ADDR   0x03
#define SENSOR_3_PIN    53
#define SENSOR_4_ADDR   0x04
#define SENSOR_4_PIN    29


#endif //_SETTINGS_H_
