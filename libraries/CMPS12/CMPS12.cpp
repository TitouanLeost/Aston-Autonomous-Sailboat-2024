#include "CMPS12.h"


CMPS12::CMPS12() : m_cmps(CMPS_TX, CMPS_RX) {}


CMPS12::~CMPS12() {}


void CMPS12::init()
{
    m_cmps.begin(9600);
}


void CMPS12::update()
{
    unsigned char high_byte, low_byte;
    unsigned int angle16;

    m_cmps.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
    while(m_cmps.available() < 2);
    high_byte = m_cmps.read();
    low_byte = m_cmps.read();
    angle16 = high_byte;           // Calculate 16 bit angle
    angle16 <<= 8;
    angle16 += low_byte;
    m_yaw_raw = angle16/10 + (float)(angle16%10)/10;
    
    m_cmps.write(CMPS_GET_PITCH);    // Request and read pitch value
    while(m_cmps.available() < 1);
    m_pitch = m_cmps.read();
    
    m_cmps.write(CMPS_GET_ROLL);     // Request and read roll value
    while(m_cmps.available() < 1);
    m_roll = m_cmps.read();
}


float CMPS12::getYaw()
{
    return m_yaw;
}


float CMPS12::getYawRaw()
{
    return m_yaw_raw;
}


int CMPS12::getPitch()
{
    return m_pitch;
}


int CMPS12::getRoll()
{
    return m_roll;
}


void CMPS12::setFilteredYaw(float yaw)
{
    m_yaw = yaw;
}