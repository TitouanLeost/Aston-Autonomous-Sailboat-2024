#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <Arduino.h>

#include <Config.h>
#include <ServoMotor.h>
#include <Algorithms.h>


/**************************************************************************
 * A base class to handle all controllers class.
 * This class contain basic functions for all controllers to use.
**************************************************************************/
class ControllerInterface
{
    public:
        /***********************************************************
         * Constructor of the class.
         * This constructor initialize the two servo motors.
        ***********************************************************/
        ControllerInterface(){
            m_mr = new ServoMotor(SERVO_RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX);
            m_ms = new ServoMotor(SERVO_SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX);
        };

        /***********************************************************
         * Destructor of the class.
         * This destructor delete the two servo motors to free 
         * up memory space.
        ***********************************************************/
        ~ControllerInterface(){
            delete m_mr;
            delete m_ms;
        };

        virtual void init() = 0;
        virtual void updateServos() = 0;


        /***********************************************************
         * Get the rudder servo motor.
         * @return A pointer to the rudder servo motor
        ***********************************************************/
        ServoMotor* mr() {return m_mr;};

        /***********************************************************
         * Get the sail servo motor.
         * @return A pointer to the sail servo motor
        ***********************************************************/
        ServoMotor* ms() {return m_ms;};

        /***********************************************************
         * Get the algorithm used.
         * @return A pointer to the algorithm used
        ***********************************************************/
        AlgorithmInterface* algo() {return m_algo;};

    protected:
        ServoMotor* m_mr = nullptr;  ///< The rudder servo motor
        ServoMotor* m_ms = nullptr;  ///< The sail servo motor
        AlgorithmInterface* m_algo = nullptr;  ///< The algorithm to use

};

#endif