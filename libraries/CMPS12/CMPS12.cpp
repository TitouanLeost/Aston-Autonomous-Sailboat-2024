#include "CMPS12.h"


CMPS12::CMPS12() : ss_cmps(CMPS_RX, CMPS_TX) {}


CMPS12::~CMPS12() {}


void CMPS12::init()
{
    Serial.println(" -> Initializing CMPS12...");
    ss_cmps.begin(9600);
    if(ss_cmps.isListening())
        Serial.println(" => CMPS12 initialized");
    calibration();
}


void CMPS12::update()
{
    unsigned char high_byte, low_byte;
    unsigned int angle16;

    ss_cmps.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
    while(ss_cmps.available() < 2);
    high_byte = ss_cmps.read();
    low_byte = ss_cmps.read();
    angle16 = high_byte;           // Calculate 16 bit angle
    angle16 <<= 8;
    angle16 += low_byte;
    m_yaw_raw = angle16/10 + (float)(angle16%10)/10;
    
    ss_cmps.write(CMPS_GET_PITCH);    // Request and read pitch value
    while(ss_cmps.available() < 1);
    m_pitch = ss_cmps.read();
    
    ss_cmps.write(CMPS_GET_ROLL);     // Request and read roll value
    while(ss_cmps.available() < 1);
    m_roll = ss_cmps.read();
}


void CMPS12::calibration()
{
    Serial.println(" -> Checking calibration status...");
    ss_cmps.write(CMPS_CALIBRATION_STATUS);
    while(ss_cmps.available() < 1);
    unsigned char status = ss_cmps.read();
    while(int(status) != 255){
        status = ss_cmps.read();
    }
    Serial.println(" => Calibration done");
}


float CMPS12::getYaw() {return m_yaw;}


float CMPS12::getYawRaw() {return m_yaw_raw;}


int CMPS12::getPitch() {return m_pitch;}


int CMPS12::getRoll() {return m_roll;}


void CMPS12::setFilteredYaw(float yaw) {m_yaw = yaw;}