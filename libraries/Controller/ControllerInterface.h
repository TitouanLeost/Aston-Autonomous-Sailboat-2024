#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <Arduino.h>

#include <Config.h>
#include <ServoMotor.h>
#include <Algorithms.h>


class ControllerInterface
{
    public:
        ControllerInterface(){
            m_mr = new ServoMotor(SERVO_RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX);
            m_ms = new ServoMotor(SERVO_SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX);
        };
        ~ControllerInterface(){
            delete m_mr;
            delete m_ms;
        };

        virtual void init() = 0;
        virtual void updateServos() = 0;

        ServoMotor* mr() {return m_mr;};
        ServoMotor* ms() {return m_ms;};
        ControlAlgorithm* algo() {return m_algo;};

    protected:
        ServoMotor* m_mr = nullptr;
        ServoMotor* m_ms = nullptr;
        ControlAlgorithm* m_algo = nullptr;

};

#endif