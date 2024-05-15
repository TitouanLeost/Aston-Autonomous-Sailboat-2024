#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <math.h>
#include <TinyGPS++.h>
#include <Config.h>


class GPS
{
    public:
        GPS();
        ~GPS();

        void init();
        void update();

        double getLat();
        double getLon();

        double getCourse();
        double getSpeed();

        int getSatellites();

        String getDate();  // Format: DDMMYY
        String getTime();  // Format: HHMMSS

        CoordLatLon getCoordLatLon();
        CoordXY getCoordXY();

    private:
        TinyGPSPlus m_gps;
};

CoordXY latLonToXY(CoordLatLon coordLatLon);


#endif