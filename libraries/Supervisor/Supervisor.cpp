#include <Supervisor.h>


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define IS_ALGO2_EQUAL_TO(value) (String(TOSTRING(ALGO2)) == String(#value))


Supervisor::Supervisor() : m_wp(WP){}


Supervisor::~Supervisor()
{
    delete m_obs;
    delete m_ctrl;
    delete m_rc;
}


void Supervisor::init(Observer* obs, Controller* ctrl, RCReceiver* rc, Logger* logger)
{
    m_obs = obs;
    m_ctrl = ctrl;
    m_rc = rc;
    m_logger = logger;

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
            if(m_mission_finished)
                break;

            m_ctrl->setUpdate(true);
            if(!m_waypoint_is_reached && isWaypointReached()){
                m_waypoint_is_reached = true;
                if (IS_ALGO2_EQUAL_TO(NoAlgorithm))
                    nextWaypoint();
                else{
                    m_algo_type = m_ctrl->setAlgo(2);
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
    m_algo_type = m_ctrl->setAlgo(1);
    CoordLatLon a = m_obs->gps()->getCoordLatLon();
    CoordLatLon b = m_wp[m_current_wp];
    m_ctrl->algo()->updateWaypoint(a, b);
}


void Supervisor::nextWaypoint()
{
    m_waypoint_is_reached = false;
    m_current_wp++;
    if(m_current_wp == NB_WP) {
        m_mission_finished = true;
        m_ctrl->setUpdate(false);
        m_ctrl->mr()->setPercent(0.5);
        m_ctrl->ms()->setPercent(0.5);
        m_logger->close();
    }
    else {
        if(m_algo_type == 2)
            m_algo_type = m_ctrl->setAlgo(1);

        CoordLatLon a = m_wp[m_current_wp-1];
        CoordLatLon b = m_wp[m_current_wp];
        m_ctrl->algo()->updateWaypoint(a, b);
    }
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
    return (((m_algo_type == 2) && ((millis() - m_algo2_start_time) > ALGO2_DURATION*1000)) ? true : false);
}
