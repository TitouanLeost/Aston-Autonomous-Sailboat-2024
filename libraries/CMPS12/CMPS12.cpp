#include "CMPS12.h"


CMPS12::CMPS12() {}


CMPS12::~CMPS12() {}


void CMPS12::init()
{
    Serial.println(" -> Initializing CMPS12...");
    SERIAL_CMPS.begin(9600);
    calibration();
    Serial.println(" => CMPS12 initialized");

    m_yaw = 0;
    m_yaw_raw = 0;
}


void CMPS12::update()
{
    unsigned char high_byte, low_byte;
    unsigned int angle16;

    SERIAL_CMPS.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
    while(SERIAL_CMPS.available() < 2);
    high_byte = SERIAL_CMPS.read();
    low_byte = SERIAL_CMPS.read();
    angle16 = high_byte;           // Calculate 16 bit angle
    angle16 <<= 8;
    angle16 += low_byte;
    m_yaw_raw = angle16/10 + (float)(angle16%10)/10;
    
    SERIAL_CMPS.write(CMPS_GET_PITCH);    // Request and read pitch value
    while(SERIAL_CMPS.available() < 1);
    m_pitch = SERIAL_CMPS.read();
    
    SERIAL_CMPS.write(CMPS_GET_ROLL);     // Request and read roll value
    while(SERIAL_CMPS.available() < 1);
    m_roll = SERIAL_CMPS.read();
}


void CMPS12::setFilteredYaw(float yaw) {m_yaw = yaw;}


float CMPS12::getYaw() {return m_yaw;}
float CMPS12::getYawRaw() {return m_yaw_raw;}
int CMPS12::getPitch() {return m_pitch;}
int CMPS12::getRoll() {return m_roll;}


void CMPS12::calibration()
{
    if(CMPS_SAVE_CALIBRATION){
        Serial.println("   -> Erasing calibration profile...");

        SERIAL_CMPS.write(0xE0);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();
        SERIAL_CMPS.write(0xE5);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();
        SERIAL_CMPS.write(0xE2);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();

        Serial.println("   => Calibration profile erased");
    }

    Serial.println("   -> Checking calibration status...");

    SERIAL_CMPS.write(CMPS_CALIBRATION_STATUS);
    while(SERIAL_CMPS.available() < 1);
    unsigned char status = SERIAL_CMPS.read();
    while(int(status) != 255) {
        SERIAL_CMPS.write(CMPS_CALIBRATION_STATUS);
        while(SERIAL_CMPS.available() < 1);
        status = SERIAL_CMPS.read();
        Serial.println(int(status));
    }

    Serial.println("   => Calibration done");

    if(CMPS_SAVE_CALIBRATION){
        Serial.println("   -> Saving calibration profile...");

        SERIAL_CMPS.write(0xF0);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();
        SERIAL_CMPS.write(0xF5);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();
        SERIAL_CMPS.write(0xF6);
        while(SERIAL_CMPS.available() < 1);
        SERIAL_CMPS.read();

        Serial.println("   => Calibration profile saved");
    }
}
