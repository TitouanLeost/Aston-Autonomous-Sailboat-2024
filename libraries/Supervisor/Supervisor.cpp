#include <Supervisor.h>


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define IS_ALGO2_EQUAL_TO(value) (String(TOSTRING(ALGO2)) == String(#value))


Supervisor::Supervisor() : m_wp(WP){}


Supervisor::~Supervisor(){}


void Supervisor::init(Observer* obs, Controller* ctrl, RCReceiver* rc)
{
    m_obs = obs;
    m_ctrl = ctrl;
    m_rc = rc;

    startMission();
}


void Supervisor::updateMission()
{
    switch(m_rc->isReceiving()){
        case true:
            m_ctrl->setUpdate(false);
            m_rc->update();
            m_ctrl->mr()->setPercent(m_rc->getCmdRudder());
            m_ctrl->ms()->setPercent(m_rc->getCmdSail());
            break;

        case false:
            m_ctrl->setUpdate(true);
            if(isWaypointReached()){
                m_start_time = millis();
                if (IS_ALGO2_EQUAL_TO(NoAlgorithm))
                    nextWaypoint();
                else{
                    m_num_algo = m_ctrl->setAlgo(2);
                    m_algo2_start_time = millis();
                }
            }
            if(isAlgo2Finished())
                nextWaypoint();

            break;
    }
}


void Supervisor::startMission()
{
    m_num_algo = m_ctrl->setAlgo(1);
    CoordLatLon a = m_obs->gps()->getCoordLatLon();
    CoordLatLon b = m_wp[m_current_wp];
    m_ctrl->algo()->updateWaypoint(a, b);   
}


void Supervisor::nextWaypoint()
{
    m_current_wp++;
    if(m_num_algo == 2) 
        m_num_algo = m_ctrl->setAlgo(1);

    CoordLatLon a = m_wp[m_current_wp-1];
    CoordLatLon b = m_wp[m_current_wp];
    m_ctrl->algo()->updateWaypoint(a, b);
}


bool Supervisor::isWaypointReached()
{
    CoordXY wp = latLonToXY(m_wp[m_current_wp]);
    CoordXY pos = m_obs->gps()->getCoordXY();
    float dist = sqrt(pow(wp.x - pos.x, 2) + pow(wp.y - pos.y, 2));
    return (dist < WP_RADIUS ? true : false);
}


bool Supervisor::isAlgo2Finished()
{
    return (((m_num_algo == 2) && ((millis() - m_algo2_start_time) > ALGO2_DURATION*1000)) ? true : false);
}
