#include <Observer.h>


Observer::Observer()
{
}


Observer::~Observer() {}


void Observer::init()
{
    m_cmps.init();
}


void Observer::updateSensors()
{
    m_cmps.update();
}


void Observer::fusion()
{ 
    float yaw = YAW_FILTER * m_cmps.getYawRaw() + (1 - YAW_FILTER) * m_cmps.getYaw();  // Low pass filter for yaw
    m_cmps.setFilteredYaw(yaw);
}


CMPS12 Observer::cmps() {return m_cmps;}