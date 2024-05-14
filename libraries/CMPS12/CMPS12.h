#ifndef CMPS12_H
#define CMPS12_H

#include <SoftwareSerial.h>
#include <Config.h>


class CMPS12
{
    public:
        CMPS12();
        ~CMPS12();

        void init();
        void update();

        int getAngle8();
        float getAngle();
        int getPitch();
        int getRoll();

    private:
        SoftwareSerial m_cmps;

        char m_pitch, m_roll;
        unsigned char m_angle8;
        float m_angle;
};

#endif