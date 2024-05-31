#include <Tools.h>

CoordXY latLonToXY(CoordLatLon coordLatLon) 
{
    CoordXY coord;
    double lat = coordLatLon.lat;
    double lon = coordLatLon.lon;

    double x = EARTH_RADIUS * cos(lat*M_PI/180) * (lon - REF_LON) * M_PI/180;
    double y = EARTH_RADIUS * (lat - REF_LAT) * M_PI/180;

    coord.x = x;
    coord.y = y;

    return coord;
}


float sawtooth(float x)
{
    return 2*atan(tan(x/2));
}