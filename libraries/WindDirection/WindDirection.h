#ifndef WINDDIRECTION_H
#define WINDDIRECTION_H

#include <Arduino.h>
#include <Config.h>

class WindDirection
{
    public:
        WindDirection();
        ~WindDirection();

        void init();
        void update();

        double getWindDirection();

    private:
        int m_wind_direction;
};

#endif