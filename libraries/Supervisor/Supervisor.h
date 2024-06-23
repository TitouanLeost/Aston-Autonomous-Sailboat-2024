#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <Arduino.h>
#include <time.h>

#include <Config.h>
#include <Observer.h>
#include <Controller.h>
#include <RCReceiver.h>

using namespace std;


/**************************************************************************
 * A class to handle the supervisor.
 * This class allows updating the mission of the boat according to the 
 * section "MISSION CONFIG" in the file Config.h. The mission
 * is divided into two parts: 
 * - the first part is to reach the next waypoint
 * - the second part is to perform a task from this waypoint
 * 
 * To perform these tasks, the supervisor can select two kinds of algorithms: 
 * type 1 algorithms are used to perform the first part of the mission while
 * type 2 algorithms are used to perform the second part.
 * You can change the algorithms used for the mission, the waypoints 
 * to reach, and the duration of the type 2 algorithm in the file Config.h.
***************************************************************************/
class Supervisor
{
    public:
        /*************************************************************
         * Constructor of the class.
         * This constructor initializes the list of waypoints to 
         * reach.
        *************************************************************/
        Supervisor();

        /*************************************************************
         * Destructor of the class.
         * This destructor deletes the pointers to the observer,
         * controller, and RC receiver to free up memory space.
        *************************************************************/
        ~Supervisor();
        
        /*************************************************************
         * Initialize the supervisor.
         * This function initializes the supervisor with the observer,
         * the controller, and the RC receiver. It also starts the
         * mission by calling the startMission() method.
         * @param obs A pointer to the observer used
         * @param ctrl A pointer to the controller used
         * @param rc A pointer to the RC receiver used
        *************************************************************/
        void init(Observer* obs, Controller* ctrl, RCReceiver* rc);

        /*************************************************************
         * Update the mission.
         * This function updates the mission first by checking the
         * status of the RC receiver to determine whether the boat 
         * should be autonomous or remotely controlled. Then, it 
         * checks if the boat has reached the current waypoint. If it 
         * has, it either switches to the next waypoint or tells the
         * controller to use the type 2 algorithm for the specified
         * duration, before switching to the next waypoint and reusing 
         * the type 1 algorithm.
        *************************************************************/
        void updateMission();

    private:
        /*************************************************************
         * Start the mission.
         * This function starts the mission of the boat by taking
         * the current position of the boat as the first waypoint and
         * calling the nextWaypoint() method to set the goal of the
         * type 1 algorithm.
        *************************************************************/
        void startMission();

        /*************************************************************
         * Switch to the next waypoint.
         * This function updates the current waypoint to reach by 
         * calling the nextWaypoint() method to update the goal of
         * the type 1 algorithm.
        *************************************************************/
        void nextWaypoint();

        /*************************************************************
         * Check if the waypoint is reached.
         * This function checks if the boat has reached the current
         * waypoint.
         * @return True if the waypoint is reached, false otherwise
        *************************************************************/
        bool isWaypointReached();

        /*************************************************************
         * Check if the type 2 algorithm is finished.
         * This function checks if the type 2 algorithm has been run
         * for its entire duration.
         * @return True if the type 2 algorithm is finished, 
         * false otherwise
        *************************************************************/
        bool isAlgo2Finished();

        Observer* m_obs = nullptr;  ///< The observer used
        Controller* m_ctrl = nullptr;  ///< The controller used
        RCReceiver* m_rc = nullptr;  ///< The RC receiver used

        CoordLatLon m_wp[NB_WP];  ///< The list of waypoints
        int m_current_wp = 0;  ///< The current waypoint index
        unsigned long m_algo2_start_time;  ///< The start time of the algorithm 2
        int m_algo_type;  ///< The type of the algorithm to use (1 or 2)
};

#endif