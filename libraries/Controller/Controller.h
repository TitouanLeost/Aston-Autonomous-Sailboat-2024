#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <math.h>

#include <Config.h>
#include <ControllerInterface.h>
#include <ServoMotor.h>


/**************************************************************************
 * A class to handle the Line Following controller.
 * This class allow to update the servos motors with the Line Following
 * algorithm by using the data from the observer.
**************************************************************************/
class ControllerLF : public ControllerInterface
{
    public:
        ControllerLF();
        ~ControllerLF();


        /********************************************************
         * Initialize the controller.
         * This function initialize the two servo motors.
        ********************************************************/
        void init();

        /********************************************************
         * Update the servo motors.
         * This function update the servo motors with the data 
         * from the Line Following algorithm.
        ********************************************************/
        void updateServos();

    private:

};

#endif