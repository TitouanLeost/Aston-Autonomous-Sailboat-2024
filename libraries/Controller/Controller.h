#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <math.h>

#include <Config.h>
#include <ControllerInterface.h>
#include <ServoMotor.h>


class ControllerLF : public ControllerInterface
{
    public:
        ControllerLF();
        ~ControllerLF();

        void init();
        void updateServos();

    private:

};

#endif