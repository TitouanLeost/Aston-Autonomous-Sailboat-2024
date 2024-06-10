#include <RCReceiver.h>


RCReceiver::RCReceiver() {}


RCReceiver::~RCReceiver() {}


void RCReceiver::init()
{
    m_last_pulse = 0;
    m_rudder_pulse = 1500;
    m_sail_pulse = 1500;
    m_offset_min[RUDDER_CH] = RUDDER_OFFSET_MIN;
    m_offset_max[RUDDER_CH] = RUDDER_OFFSET_MAX;
    m_offset_min[SAIL_CH] = SAIL_OFFSET_MIN;
    m_offset_max[SAIL_CH] = SAIL_OFFSET_MAX;
}


void RCReceiver::update()
{
    m_rudder_pulse = pulseIn(RUDDER_CH_PIN, HIGH);
    m_sail_pulse = pulseIn(SAIL_CH_PIN, HIGH);
}

void RCReceiver::checkRC(int pin)
{
    m_last_pulse = millis();
}


bool RCReceiver::isReceiving()
{
    return ((millis() - m_last_pulse) < 100  ? true : false);
}


float RCReceiver::convertToPercent(unsigned long pulse, int ch)
{
    return ((float)pulse - (float)m_offset_min[ch]) / ((float)m_offset_max[ch] - (float)m_offset_min[ch]);
}


float RCReceiver::getCmdRudder() {return convertToPercent(m_rudder_pulse, RUDDER_CH);}
float RCReceiver::getCmdSail() {return convertToPercent(m_sail_pulse, SAIL_CH);}