#ifndef RCRECEIVER_H
#define RCRECEIVER_H

#include <Arduino.h>

#include <Config.h>


/***********************************************************************************************
 * A class to handle the RC receiver.
 * This class allows to get the commands of the rudder and the sail from the RC receiver.
************************************************************************************************/
class RCReceiver
{
    public:
        RCReceiver();
        ~RCReceiver();

        /***********************************************************************
         * Initialize the RC receiver.
         * This function initializes all the class variables.
        ************************************************************************/
        void init();

        /***********************************************************************
         * Update the RC receiver.
         * This function updates the pulse of the rudder and the sail and 
         * filters the received pulses.
        ************************************************************************/
        void update();


        /***********************************************************************
         * Reset the last pulse time.
         * This function is called when a pulse is received via an interrupt.
         * It is used to check if the RC receiver is still receiving.
        ************************************************************************/
        void checkRC();

        /***********************************************************************
         * Check if the RC receiver is receiving.
         * @return True if the RC receiver is receiving, false otherwise
        ************************************************************************/
        bool isReceiving();

        /***********************************************************************
         * Convert a pulse to a percentage between 0.0 and 1.0.
         * This function converts a pulse to a percentage using the minimum and
         * maximum offsets of the channel.
         * @param pulse The pulse to convert
         * @param ch The channel that gives the pulse
         * @return The percentage of the pulse (between 0.0 and 1.0)
        ************************************************************************/
        float convertToPercent(unsigned long pulse, int ch);


        /***********************************************************************
         * Get the command of the rudder.
         * @return The command of the rudder between 0.0 and 1.0
        ************************************************************************/
        float getCmdRudder();

        /***********************************************************************
         * Get the command of the sail.
         * @return The command of the sail between 0.0 and 1.0
        ************************************************************************/
        float getCmdSail();

    private:
        unsigned long m_last_pulse;  // Last time a pulse was received
        unsigned long m_rudder_pulse;  // Filtered pulse of the rudder
        unsigned long m_rudder_pulse_raw;  // Raw pulse of the rudder
        unsigned long m_sail_pulse;  // Filtered pulse of the sail
        unsigned long m_sail_pulse_raw;  // Raw pulse of the sail
        unsigned long m_offset_min[NB_CHANNELS];  // Minimum offset of the channels
        unsigned long m_offset_max[NB_CHANNELS];  // Maximum offset of the channels
};

#endif