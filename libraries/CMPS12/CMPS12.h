#ifndef CMPS12_H
#define CMPS12_H

#include <Arduino.h>

#include <Config.h>
#include <ServoMotor.h>


/***********************************************************************************************
 * A class to handle the CMPS12.
 * This class allows to get the yaw (filtered or not), pitch and roll of the CMPS12.
***********************************************************************************************/
class CMPS12
{
    public:
        CMPS12();
        ~CMPS12();

        /***********************************************************************
         * Initialize the CMPS12.
         * This function initializes the serial connection with the CMPS12 and 
         * check that the CMPS12 is calibrated by calling the calibration() 
         * method.
        ***********************************************************************/
        void init();

        /***********************************************************************
         * Update the yaw, pitch and roll of the CMPS12.
        ***********************************************************************/
        void update();


        /***********************************************************************
         * Set the filtered yaw.
         * @param yaw The filtered yaw
        ***********************************************************************/
        void setFilteredYaw(float yaw);


        /***********************************************************************
         * Get the filtered yaw of the boat.
         * @return The filtered yaw in degrees (0 to 360)
        ***********************************************************************/
        float getYaw();

        /***********************************************************************
         * Get the raw yaw of the boat.
         * @return The raw yaw in degrees (0 to 360)
        ***********************************************************************/
        float getYawRaw();

        /***********************************************************************
         * Get the pitch of the boat.
         * @return The pitch in degrees (-90 to 90)
        ***********************************************************************/
        int getPitch();

        /***********************************************************************
         * Get the roll of the boat.
         * @return The roll in degrees (-90 to 90)
        ***********************************************************************/
        int getRoll();

    private:
        /***********************************************************************
         * Check the calibration status of the CMPS12 compass.
        ***********************************************************************/
        void calibration();


        char m_pitch;  ///< The pitch of the boat in degrees (-90 to 90)
        char m_roll;  ///< The roll of the boat in degrees (-90 to 90)
        float m_yaw;  ///< The filtered yaw of the boat in degrees (0 to 360)
        float m_yaw_raw;  ///< The raw yaw of the boat in degrees (0 to 360)
        int m_cpt = 0;  ///< A counter to check the calibration status

        ServoMotor* m_mr = nullptr;
        ServoMotor* m_ms = nullptr;
};

#endif