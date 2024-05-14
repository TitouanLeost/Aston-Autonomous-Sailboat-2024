#ifndef OBSERVER_H
#define OBSERVER_H

#include <Config.h>
#include <CMPS12.h>


class Observer
{
    public:
        Observer();
        ~Observer();

        void init();
        void updateSensors();
        void fusion();

        CMPS12 cmps();

    private:
        CMPS12 m_cmps;


};


#endif