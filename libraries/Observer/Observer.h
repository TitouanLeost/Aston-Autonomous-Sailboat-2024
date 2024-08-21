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
 * This class allows to update the sensors and to process the data. These
 * data are then used to feed the controller.
**************************************************************************/
class Observer
{
    public:
        /********************************************************
         * Constructor of the class.
         * This constructor initializes the sensors used by the
         * observer.
        ********************************************************/
        Observer();

        /********************************************************
         * Destructor of the class.
         * This destructor deletes the pointers to the sensors
         * to free up memory space.
        ********************************************************/
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
         * Get the true wind angle.
         * @return The true wind angle in degrees (0 to 360)
        ********************************************************/
        float getTrueWindAngle();

        /********************************************************
         * Get the CMPS12 sensor.
         * @return A pointer to the CMPS12
        ********************************************************/
        CMPS12* cmps();

        /********************************************************
         * Get the GPS sensor.
         * @return A pointer to the GPS
        ********************************************************/
        GPS* gps();

        /********************************************************
         * Get the wind speed sensor.
         * @return A pointer to the wind speed sensor
        ********************************************************/
        WindSpeed* ws();

        /********************************************************
         * Get the wind direction sensor.
         * @return A pointer to the wind direction sensor
        ********************************************************/
        WindDirection* wd();

    private:
        /********************************************************
         * Process the data.
         * This function is used to filter the data from the
         * CMPS and the wind direction sensor.
        ********************************************************/
        void fusion();

        /********************************************************
         * Update the true wind angle.
        ********************************************************/
        void updateTrueWindAngle();

        /********************************************************
         * Filter the angle.
         * This function is used to filter the angle between two
         * values. A lower alpha value will give more weight to 
         * the current angle and less to the previous angle.
         * @param filtered The previous filtered angle (0 to 360)
         * @param raw The current raw angle (0 to 360)
         * @param alpha The filter coefficient
         * @return The filtered angle in degrees (0 to 360)
        ********************************************************/
        float angleFilter(float filtered, float raw, float alpha);


        CMPS12* m_cmps;  ///< The CMPS sensor
        GPS* m_gps;  ///< The GPS sensor
        WindSpeed* m_ws;  ///< The wind speed sensor
        WindDirection* m_wd;  ///< The wind direction sensor

        float m_true_wind_angle;  ///< The true wind angle in degrees (0 to 360)

};


#endif