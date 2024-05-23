#include <Supervisor.h>


Supervisor::Supervisor() : m_wp(WP)
{

}


Supervisor::~Supervisor()
{

}


void Supervisor::init(Observer* obs, ControllerInterface* ctrl)
{
    m_obs = obs;
    m_ctrl = ctrl;

    #if CONTROLLER == ControllerLF
        updatePtr = &Supervisor::updateLF;
        startPtr = &Supervisor::startLF;
    #endif

    (this->*startPtr)();
}


void Supervisor::updateMission()
{
    (this->*updatePtr)();
}


void Supervisor::startLF()
{
    CoordLatLon a = m_obs->gps()->getCoordLatLon();
    CoordLatLon b = m_wp[m_current_wp];
    m_ctrl->algo()->setLine(a, b);
}


void Supervisor::updateLF()
{
    if (isWaypointReached()){
        m_current_wp++;
        if (m_current_wp >= NB_WP)
            m_current_wp = 0;
        
        CoordLatLon a = m_wp[m_current_wp-1];
        CoordLatLon b = m_wp[m_current_wp];
        m_ctrl->algo()->setLine(a, b);
    }
}


bool Supervisor::isWaypointReached()
{
    CoordXY wp = latLonToXY(m_wp[m_current_wp]);
    CoordXY pos = m_obs->gps()->getCoordXY();
    float dist = sqrt(pow(wp.x - pos.x, 2) + pow(wp.y - pos.y, 2));
    return (dist < WP_RADIUS ? true : false);
}

