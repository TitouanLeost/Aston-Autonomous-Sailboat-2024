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

        float getYaw();
        float getYawRaw();
        int getPitch();
        int getRoll();

        void setFilteredYaw(float yaw);

    private:
        SoftwareSerial m_cmps;

        char m_pitch, m_roll;
        float m_yaw, m_yaw_raw;
};

#endif