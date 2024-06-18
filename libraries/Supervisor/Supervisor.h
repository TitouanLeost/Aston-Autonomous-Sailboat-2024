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
 * This class allow to update the mission of the boat according to the 
 * section "MISSION CONFIG" in the file Config.h.
***************************************************************************/
class Supervisor
{
    public:
        Supervisor();
        ~Supervisor();
        
        /*************************************************************
         * Initialize the supervisor.
         * This function initialize the supervisor with the observer,
         * the controller and the RC receiver.
         * @param obs A pointer to the observer used
         * @param ctrl A pointer to the controller used
         * @param rc A pointer to the RC receiver used
        *************************************************************/
        void init(Observer* obs, Controller* ctrl, RCReceiver* rc);

        /*************************************************************
         * Update the mission.
         * This function update the mission of the boat.
        *************************************************************/
        void updateMission();

    private:
        /*************************************************************
         * Start the mission.
         * This function start the mission of the boat by taking
         * the current position of the boat as the first waypoint.
        *************************************************************/
        void startMission();

        /*************************************************************
         * Switch to the next waypoint.
         * This function update the current waypoint to reach.
        *************************************************************/
        void nextWaypoint();

        /*************************************************************
         * Check if the waypoint is reached.
         * This function check if the boat has reached the current
         * waypoint.
         * @return True if the waypoint is reached, false otherwise
        *************************************************************/
        bool isWaypointReached();

        /*************************************************************
         * Check if the type 2 algorithm is finished.
         * This function check if the type 2 algorithm has been runned
         * for its whole duration.
         * @return True if the type 2 algorithm is finished, 
         * false otherwise
        *************************************************************/
        bool isAlgo2Finished();

        Observer* m_obs = nullptr;  ///< The observer used
        Controller* m_ctrl = nullptr;  ///< The controller used
        RCReceiver* m_rc = nullptr;  ///< The RC receiver used

        CoordLatLon m_wp[NB_WP];  ///< The list of waypoints
        int m_current_wp = 0;  ///< The current waypoint index
        unsigned long m_algo2_start_time = 0;  ///< The start time of the algorithm 2
        int m_num_algo;  ///< The number of the algorithm to use
};

#endif