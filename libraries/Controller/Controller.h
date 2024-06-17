#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <math.h>

#include <Config.h>
#include <Algorithms.h>
#include <ServoMotor.h>


/*****************************************************************************
 * A class to handle the controller.
 * This class contain functions to initialize and update the servo motors
 * based on the data from the algorithm used for the mission. The
 * algorithm to use is defined in Config.h.
*****************************************************************************/
class Controller
{
    public:
        /***********************************************************
         * Constructor of the class.
         * This constructor initialize the two servo motors and the
         * algorithm to use defined in Config.h.
        ***********************************************************/
        Controller();

        /***********************************************************
         * Destructor of the class.
         * This destructor delete the two servo motors and the 
         * algorithm to free up memory space.
        ***********************************************************/
        ~Controller();


        /***********************************************************
         * Initialize the controller.
         * This function initialize the two servo motors.
        ***********************************************************/
        void init(Observer* obs);

        /***********************************************************
         * Update the servo motors.
         * This function update the servo motors with the data 
         * from the algorithm.
        ***********************************************************/
        void updateServos();


        void setUpdate(bool update);


        /***********************************************************
         * Get the rudder servo motor.
         * @return A pointer to the rudder servo motor
        ***********************************************************/
        ServoMotor* mr();

        /***********************************************************
         * Get the sail servo motor.
         * @return A pointer to the sail servo motor
        ***********************************************************/
        ServoMotor* ms();

        /***********************************************************
         * Get the algorithm used.
         * @return A pointer to the algorithm used
        ***********************************************************/
        AlgorithmInterface* algo();

    private:
        ServoMotor* m_mr = nullptr;  ///< The rudder servo motor
        ServoMotor* m_ms = nullptr;  ///< The sail servo motor
        AlgorithmInterface* m_algo = nullptr;  ///< The algorithm to use

        bool m_update = true;  ///< A flag to update the servo motors
};

#endif