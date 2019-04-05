/* gaussian_location.h */


#ifndef _GAUSSIAN_LOCATION_H_
#define _GAUSSIAN_LOCATION_H_


/* Holds a gaussian value */
typedef struct {
    double mean;
    double sigma2;
} gaussian_t;


/* gaussian_location_t
 * Defines the location of the robot in mm from
 * the top left of the maze(starting point), theta
 * is defined as the angle in degrees counter-clockwise
 * from the x axis
 * 
 * (0,0) starts in the top left corner of the maze inside of the maze
 * +---------> +x axis
 * |
 * |
 * |
 * V
 * +y axis
 * 
 * */
typedef struct {
    gaussian_t x;
    gaussian_t y;
    gaussian_t theta;
} gaussian_location_t;

#endif //_GAUSSIAN_LOCATION_H_