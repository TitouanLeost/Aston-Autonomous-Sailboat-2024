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

        void init();
        void update();

        void rotation();
        double getWindSpeed();

    private:
        volatile int m_nb_rotations;
        volatile unsigned long m_contact_time;
        volatile unsigned long m_average_time;
        volatile double m_wind_speed;
};

#endif