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

    fusion();
    updateTrueWindAngle();
}


float Observer::getTrueWindAngle() {return m_true_wind_angle;}
CMPS12* Observer::cmps() {return m_cmps;}
GPS* Observer::gps() {return m_gps;}
WindSpeed* Observer::ws() {return m_ws;}
WindDirection* Observer::wd() {return m_wd;}


void Observer::fusion()
{ 
    float yaw = angleFilter(m_cmps->getYaw(), m_cmps->getYawRaw(), YAW_FILTER);  // Low pass filter for yaw
    m_cmps->setFilteredYaw(yaw);

    float wind_direction = angleFilter(m_wd->getWindDirection(), m_wd->getRawWindDirection(), WIND_DIRECTION_FILTER);  // Low pass filter for wind direction
    m_wd->setFilteredWindDirection(wind_direction);
}


void Observer::updateTrueWindAngle()
{
    float SOG = gps()->getSpeed();
    float COG = cmps()->getYaw();

    float AWD = ((float)(((int)(wd()->getWindDirection() + cmps()->getYaw()))%360))/180*M_PI;
    float AWS = ws()->getWindSpeed();

    float u = -SOG*sin(COG) + AWS*sin(AWD);
    float v = -SOG*cos(COG) + AWS*cos(AWD);

    m_true_wind_angle = (float)(((int)((atan2(u,v)+2*M_PI)*180/M_PI))%360);
}


float Observer::angleFilter(float filtered, float raw, float alpha)
{
    filtered = wrap360(filtered + alpha*wrap360(raw - filtered));
    if(filtered < 0)
        filtered += 360;
    return filtered;
}
