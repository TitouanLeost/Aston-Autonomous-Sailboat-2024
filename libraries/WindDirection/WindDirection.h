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

        float getWindDirection();
        float getRawWindDirection();

        void setFilteredWindDirection(float wind_direction);

    private:
        float m_raw_wind_direction;
        float m_wind_direction;
};

#endif