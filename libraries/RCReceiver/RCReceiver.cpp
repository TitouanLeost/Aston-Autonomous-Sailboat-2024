#include <RCReceiver.h>


RCReceiver::RCReceiver() {}


RCReceiver::~RCReceiver() {}


void RCReceiver::init()
{
    m_last_pulse = 0;
    m_rudder_pulse = 1500;
    m_rudder_pulse_raw = 1500;
    m_sail_pulse = 1500;
    m_sail_pulse_raw = 1500;
    m_offset_min[RUDDER_CH] = RUDDER_OFFSET_MIN;
    m_offset_max[RUDDER_CH] = RUDDER_OFFSET_MAX;
    m_offset_min[SAIL_CH] = SAIL_OFFSET_MIN;
    m_offset_max[SAIL_CH] = SAIL_OFFSET_MAX;

    pinMode(RUDDER_CH_PIN, INPUT);
    pinMode(SAIL_CH_PIN, INPUT);
}


void RCReceiver::update()
{
    m_rudder_pulse_raw = pulseIn(RUDDER_CH_PIN, HIGH);
    m_sail_pulse_raw = pulseIn(SAIL_CH_PIN, HIGH);

    m_rudder_pulse = PULSE_FILTER * m_rudder_pulse + (1 - PULSE_FILTER) * m_rudder_pulse_raw;
    m_sail_pulse = PULSE_FILTER * m_sail_pulse + (1 - PULSE_FILTER) * m_sail_pulse_raw;
}

void RCReceiver::checkRC()
{
    m_last_pulse = millis();
}


bool RCReceiver::isReceiving()
{
    m_is_receiving = (millis() - m_last_pulse < 100 ? true : false);
    return m_is_receiving;
}


bool RCReceiver::status() {return m_is_receiving;}
float RCReceiver::getCmdRudder() {return convertToPercent(m_rudder_pulse, RUDDER_CH);}
float RCReceiver::getCmdSail() {return convertToPercent(m_sail_pulse, SAIL_CH);}


float RCReceiver::convertToPercent(unsigned long pulse, int ch)
{
    return ((float)pulse - (float)m_offset_min[ch]) / ((float)m_offset_max[ch] - (float)m_offset_min[ch]);
}