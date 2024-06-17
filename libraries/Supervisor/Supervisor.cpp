#include <Supervisor.h>


Supervisor::Supervisor() : m_wp(WP){}


Supervisor::~Supervisor(){}


void Supervisor::init(Observer* obs, Controller* ctrl, RCReceiver* rc)
{
    m_obs = obs;
    m_ctrl = ctrl;
    m_rc = rc;

    startMission();
}


void Supervisor::startMission()
{
    CoordLatLon a = m_obs->gps()->getCoordLatLon();
    CoordLatLon b = m_wp[m_current_wp];
    m_ctrl->algo()->setLine(a, b);   
}


void Supervisor::updateMission()
{
    m_ctrl->setUpdate(true);

    if (m_rc->isReceiving()){
        m_ctrl->setUpdate(false);
        m_rc->update();
        m_ctrl->mr()->setPercent(m_rc->getCmdRudder());
        m_ctrl->ms()->setPercent(m_rc->getCmdSail());
    }

    else if (isWaypointReached()){
        m_current_wp++;
        if (m_current_wp >= NB_WP)
            m_current_wp = 0;
        
        CoordLatLon a = m_wp[m_current_wp-1];
        CoordLatLon b = m_wp[m_current_wp];
        m_ctrl->algo()->setLine(a, b);

        Serial.println("Waypoint reached");
        Serial.print("Next waypoint: "); Serial.print(m_wp[m_current_wp].lat); Serial.print(", "); Serial.println(m_wp[m_current_wp].lon);
    }
}


bool Supervisor::isWaypointReached()
{
    CoordXY wp = latLonToXY(m_wp[m_current_wp]);
    CoordXY pos = m_obs->gps()->getCoordXY();
    float dist = sqrt(pow(wp.x - pos.x, 2) + pow(wp.y - pos.y, 2));
    return (dist < WP_RADIUS ? true : false);
}

