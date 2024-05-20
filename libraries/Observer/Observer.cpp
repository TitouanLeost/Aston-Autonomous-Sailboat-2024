#include <Observer.h>


Observer::Observer()
{
}


Observer::~Observer() {}


void Observer::init()
{
    Serial.println("#########################");
    Serial.println("Initializing sensors...");
    m_cmps.init();
    m_gps.init();
    Serial.println("Sensors initialized");
    Serial.println("######################### \n");
}


void Observer::updateSensors()
{
    m_cmps.update();
    m_gps.update();
}


void Observer::fusion()
{ 
    float yaw = YAW_FILTER * m_cmps.getYawRaw() + (1 - YAW_FILTER) * m_cmps.getYaw();  // Low pass filter for yaw
    m_cmps.setFilteredYaw(yaw);
}


CMPS12 Observer::cmps() {return m_cmps;}
GPS Observer::gps() {return m_gps;}