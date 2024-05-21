#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <Config.h>
#include <ServoMotor.h>


class Controller
{
    public:
        Controller();
        ~Controller();

        void init();
        void updateServos();

        ServoMotor* mr();
        ServoMotor* ms();

    private:
        ServoMotor* m_mr;
        ServoMotor* m_ms;

};

#endif