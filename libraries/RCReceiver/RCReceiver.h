#ifndef RCRECEIVER_H
#define RCRECEIVER_H

#include <Arduino.h>

#include <Config.h>


class RCReceiver
{
    public:
        RCReceiver();
        ~RCReceiver();

        void init();
        void update();

        void checkRC();
        bool isReceiving();
        float convertToPercent(unsigned long pulse, int ch);

        float getCmdRudder();
        float getCmdSail();

    private:
        unsigned long m_last_pulse;
        unsigned long m_rudder_pulse;
        unsigned long m_rudder_pulse_raw;
        unsigned long m_sail_pulse;
        unsigned long m_sail_pulse_raw;
        unsigned long m_offset_min[NB_CHANNELS];
        unsigned long m_offset_max[NB_CHANNELS];
};

#endif