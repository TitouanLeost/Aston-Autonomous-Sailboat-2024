#ifndef WINDSPEED_H
#define WINDSPEED_H

#include <Arduino.h>
#include <time.h>

#include <Config.h>


/***************************************************************************************
 * A class to handle the wind speed.
 * This class allow to get the wind speed in kph.
 ***************************************************************************************/
class WindSpeed
{
    public:
        WindSpeed();
        ~WindSpeed();

        /******************************************************************
         * Initialize the different variables of the class.
        ******************************************************************/
        void init();

        /******************************************************************
         * Update the wind speed if the anemometer is not rotating.
         * This function set the wind speed to 0 if the anemometer is
         * not rotating for more than 5 seconds.
        ******************************************************************/
        void update();

        /******************************************************************
         * Compute the wind speed.
         * This function increment the number of rotations of the 
         * anemometer and calculate the wind speed in kph.
        ******************************************************************/
        void rotation();

        /******************************************************************
         * Get the wind speed.
         * @return The wind speed in kph
        ******************************************************************/
        double getWindSpeed();

    private:
        volatile int m_nb_rotations;  ///< Number of rotations of the anemometer
        volatile unsigned long m_contact_time;  ///< Minimum time between two rotations (avoid false detection)
        volatile unsigned long m_average_time;  ///< Time to calculate the average wind speed
        volatile double m_wind_speed;  ///< Wind speed in kph
};

#endif