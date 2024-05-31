#ifndef WINDDIRECTION_H
#define WINDDIRECTION_H

#include <Arduino.h>
#include <Config.h>


/************************************************************************************************
 * A class to handle the wind direction.
 * This class allow to get the wind direction (raw and filtered) in degrees (between 0 and 360).
************************************************************************************************/
class WindDirection
{
    public:
        WindDirection();
        ~WindDirection();
        
        /********************************************************************
         * Initialize the wind direction.
         * This function initializes the wind direction at 0.
        ********************************************************************/
        void init();

        /********************************************************************
         * Update the wind direction.
         * This function reads the analog value of the wind direction sensor
         * and update the raw wind direction.
        ********************************************************************/
        void update();


        /********************************************************************
         * Get the filtered wind direction.
         * @return Thefiltered wind direction in degrees (0 to 360)
        ********************************************************************/
        float getWindDirection();

        /********************************************************************
         * Get the raw wind direction.
         * @return The raw wind direction in degrees (0 to 360)
        ********************************************************************/
        float getRawWindDirection();


        /********************************************************************
         * Set the filtered wind direction.
         * @param wind_direction The filtered wind direction in degrees
        ********************************************************************/
        void setFilteredWindDirection(float wind_direction);

    private:
        float m_raw_wind_direction;  ///< Raw wind direction in degrees (0 to 360)
        float m_wind_direction;  ///< Filtered wind direction in degrees (0 to 360)
};

#endif