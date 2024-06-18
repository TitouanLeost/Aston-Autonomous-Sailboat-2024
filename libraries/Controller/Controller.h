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
         * This constructor initialize the two servo motors.
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


        /***********************************************************
         * Set the algorithm to use.
         * This function set the algorithm to use for the mission.
         * It allows to switch between type 1 and type 2 algorithms
         * during the mission.
         * @param num The number of the algorithm to use
         * @return The number of the algorithm used
        ***********************************************************/
        int setAlgo(int num);

        /***********************************************************
         * Set the update flag.
         * This function set the update flag to update the servo
         * motors. If set to false, the servo motors will not be
         * updated.
         * @param update The update flag
        ***********************************************************/
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
         * @return A pointer to the algorithm currently used
        ***********************************************************/
        AlgorithmInterface* algo();

    private:
        ServoMotor* m_mr = nullptr;  ///< The rudder servo motorm
        ServoMotor* m_ms = nullptr;  ///< The sail servo motor
        AlgorithmInterface* m_algo = nullptr;  ///< The algorithm used
        ALGO1* m_algo1 = nullptr;  ///< The type 1 algorithm used
        ALGO2* m_algo2 = nullptr;  ///< The type 2 algorithm used

        bool m_update = true;  ///< A flag to update the servo motors
};

#endif