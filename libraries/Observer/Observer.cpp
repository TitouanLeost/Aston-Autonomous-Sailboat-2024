#include <Observer.h>


Observer::Observer()
{
    m_cmps = new CMPS12();
    m_gps = new GPS();
    m_ws = new WindSpeed();
    m_wd = new WindDirection();
}


Observer::~Observer() 
{
    delete m_cmps;
    delete m_gps;
    delete m_ws;
    delete m_wd;
}


void Observer::init()
{
    Serial.println("#########################");
    Serial.println("Initializing sensors...");
    m_cmps->init();
    m_gps->init();
    m_ws->init();
    m_wd->init();
    Serial.println("Sensors initialized");
    Serial.println("######################### \n");
}


void Observer::updateSensors()
{
    m_cmps->update();
    m_gps->update();
    m_ws->update();
    m_wd->update();
}


void Observer::fusion()
{ 
    float yaw = YAW_FILTER * m_cmps->getYawRaw() + (1 - YAW_FILTER) * m_cmps->getYaw();  // Low pass filter for yaw
    m_cmps->setFilteredYaw(yaw);
}


CMPS12* Observer::cmps() {return m_cmps;}
GPS* Observer::gps() {return m_gps;}
WindSpeed* Observer::ws() {return m_ws;}
WindDirection* Observer::wd() {return m_wd;}