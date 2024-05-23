#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <Arduino.h>

#include <Config.h>
#include <Observer.h>
#include <Controller.h>

using namespace std;


class Supervisor
{
    public:
        Supervisor();
        ~Supervisor();

        void init(Observer* obs, ControllerInterface* ctrl);
        void updateMission();

        void startLF();
        void updateLF();

        bool isWaypointReached();

    private:
        Observer* m_obs = nullptr;
        ControllerInterface* m_ctrl = nullptr;
        CoordLatLon m_wp[NB_WP];
        int m_current_wp = 0;

        void (Supervisor::*updatePtr)();
        void (Supervisor::*startPtr)();

};

#endif