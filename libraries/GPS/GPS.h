#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <math.h>
#include <TinyGPS++.h>
#include <Config.h>
#include <Tools.h>


/***************************************************************************************
 * A class to handle the GPS.
 * This class allow to get the coordinates, the course and the speed of the boat. 
 * Moreover, it contains a method to get the number of satellites used by the GPS and
 * two methods to get the date and the time (usefull for logging data).
***************************************************************************************/
class GPS
{
    public:
        GPS();
        ~GPS();

        /********************************************************************
         * Initialize the GPS.
         * This function initializes the serial connection with the GPS.
        ********************************************************************/
        void init();

        /********************************************************************
         * Update the GPS data.
         * This function reads the serial data from the GPS and save them.
        ********************************************************************/
        void update();

        /********************************************************************
         * Get the latitude of the GPS.
         * @return The latitude of the GPS in degrees
        ********************************************************************/
        double getLat();

        /********************************************************************
         * Get the longitude of the GPS.
         * @return The longitude of the GPS in degrees
        ********************************************************************/
        double getLon();


        /********************************************************************
         * Get the course of the GPS.
         * @return The course of the GPS in degrees
        ********************************************************************/
        double getCourse();

        /********************************************************************
         * Get the speed of the GPS.
         * @return The speed of the GPS in kph
        ********************************************************************/
        double getSpeed();


        /********************************************************************
         * Get the number of satellites detected and used by the GPS.
         * @return The number of satellites
        ********************************************************************/
        int getSatellites();


        /********************************************************************
         * Get the date of the GPS.
         * @return The date in a string in the format DDMMYY
        ********************************************************************/
        String getDate();

        /********************************************************************
         * Get the time of the GPS.
         * @return The time in a string in the format HHMMSS
        ********************************************************************/
        String getTime();


        /********************************************************************
         * Get the coordinates (latitude, longitude) of the boat.
         * @return The coordinates (lat, lon) of the boat saved in a struct
        ********************************************************************/
        CoordLatLon getCoordLatLon();

        /********************************************************************
         * Get the coordinates (x, y) of the boat.
         * @return The coordinates (x, y) of the boat saved in a struct
        ********************************************************************/
        CoordXY getCoordXY();

    private:
        TinyGPSPlus m_gps;  ///< The GPS object
};

#endif