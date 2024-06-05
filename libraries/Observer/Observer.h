#ifndef OBSERVER_H
#define OBSERVER_H

#include <Arduino.h>

#include <Config.h>
#include <CMPS12.h>
#include <GPS.h>
#include <WindSpeed.h>
#include <WindDirection.h>


/**************************************************************************
 * A class to handle the observer.
 * This class allow to update the sensors and to process the data. Those
 * data are then used to feed the controller.
**************************************************************************/
class Observer
{
    public:
        Observer();
        ~Observer();

        /********************************************************
         * Initialize the sensors.
        ********************************************************/
        void init();

        /********************************************************
         * Update the sensors and process the data.
        ********************************************************/
        void updateSensors();

        /********************************************************
         * Process the data.
         * This function is used to filtered the data from the
         * CMPS and the wind direction sensor.
        ********************************************************/
        void fusion();


        /********************************************************
         * Update the true wind angle.
        ********************************************************/
        void updateTrueWindAngle();

        /********************************************************
         * Get the true wind angle.
         * @return The true wind angle in degrees (0 to 360)
        ********************************************************/
        float getTrueWindAngle();

        CMPS12* cmps();  ///< Get the CMPS sensor
        GPS* gps();  ///< Get the GPS sensor
        WindSpeed* ws();  ///< Get the wind speed sensor
        WindDirection* wd();  ///< Get the wind direction sensor

    private:
        CMPS12* m_cmps;  ///< The CMPS sensor
        GPS* m_gps;  ///< The GPS sensor
        WindSpeed* m_ws;  ///< The wind speed sensor
        WindDirection* m_wd;  ///< The wind direction sensor

        float m_true_wind_angle;  ///< The true wind angle in degrees (0 to 360)

};


#endif