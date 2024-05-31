#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <Arduino.h>

#include <Config.h>
#include <Observer.h>
#include <Controller.h>

using namespace std;


/**************************************************************************
 * A class to handle the supervisor.
 * This class allow to update the mission of the boat and to determine
 * which controller should be use.
***************************************************************************/
class Supervisor
{
    public:
        Supervisor();
        ~Supervisor();
        
        /*************************************************************
         * Initialize the supervisor.
         * This function initialize the supervisor with the observer
         * and the controller.
         * @param obs A pointer to the observer used
         * @param ctrl A pointer to the controller used
        *************************************************************/
        void init(Observer* obs, ControllerInterface* ctrl);

        /*************************************************************
         * Update the mission.
         * This function update the mission of the boat depending on
         * the controler selected.
        *************************************************************/
        void updateMission();


        /*************************************************************
         * Start the line following controller.
         * This function initialize the line following controller by
         * taking the current position of the boat as the first
         * waypoint.
        *************************************************************/
        void startLF();

        /*************************************************************
         * Update the line following controller.
         * This function update the line following controller by
         * checking if the boat has reached the current waypoint.
        *************************************************************/
        void updateLF();


        /*************************************************************
         * Check if the waypoint is reached.
         * This function check if the boat has reached the current
         * waypoint.
         * @return True if the waypoint is reached, false otherwise
        *************************************************************/
        bool isWaypointReached();

    private:
        Observer* m_obs = nullptr;  ///< The observer used
        ControllerInterface* m_ctrl = nullptr;  ///< The controller used
        CoordLatLon m_wp[NB_WP];  ///< The waypoints
        int m_current_wp = 0;  ///< The current waypoint index

        void (Supervisor::*updatePtr)();
        void (Supervisor::*startPtr)();

};

#endif