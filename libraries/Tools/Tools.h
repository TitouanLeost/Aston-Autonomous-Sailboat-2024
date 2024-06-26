#ifndef TOOLS_H
#define TOOLS_H

#include <math.h>

#include <Config.h>


/***************************************************************
 * Convert a latitude and a longitude to a XY coordinate.
 * This function converts a latitude and a longitude to a XY 
 * coordinate using the reference latitude and longitude.
 * @param coordLatLon The latitude and longitude to convert
 * @return The XY coordinate
***************************************************************/
CoordXY latLonToXY(CoordLatLon coordLatLon);

/***************************************************************
 * Sawtooth function.
 * This function returns the sawtooth function of x.
 * @param x The input value
 * @return The sawtooth function of x
***************************************************************/
float sawtooth(float x);

/***************************************************************
 * Wrap a value between -180 and 180.
 * Maps the real number line onto the interval [−180,180) 
 * modulo 360.
 * @param x The value to wrap
 * @return The wrapped value
***************************************************************/
float wrap360(float x);

#endif