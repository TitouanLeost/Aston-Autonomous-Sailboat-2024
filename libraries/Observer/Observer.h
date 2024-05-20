#ifndef OBSERVER_H
#define OBSERVER_H

#include <Arduino.h>
#include <Config.h>
#include <CMPS12.h>
#include <GPS.h>
#include <WindSpeed.h>


class Observer
{
    public:
        Observer();
        ~Observer();

        void init();
        void updateSensors();
        void fusion();

        CMPS12* cmps();
        GPS* gps();
        WindSpeed* ws();

    private:
        CMPS12* m_cmps;
        GPS* m_gps;
        WindSpeed* m_ws;


};


#endif