#ifndef WINDSPEED_H
#define WINDSPEED_H

#include <Arduino.h>
#include <time.h>
#include <Config.h>


class WindSpeed
{
    public:
        WindSpeed();
        ~WindSpeed();

        void update();

        void rotation();
        double getWindSpeed();

    private:
        volatile int m_nb_rotations = 0;
        volatile unsigned long m_contact_time = 0;
        volatile unsigned long m_average_time = 0;
        volatile double m_wind_speed = 0;
};

#endif