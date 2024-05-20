#include <WindDirection.h>


WindDirection::WindDirection(){}


WindDirection::~WindDirection(){}


void WindDirection::init()
{
    m_wind_direction = 0;
}


void WindDirection::update()
{
    int vane_value = analogRead(WIND_DIRECTION_PIN);
    m_wind_direction = map(vane_value, 0, 1023, 0, 360);
}


double WindDirection::getWindDirection() {return m_wind_direction;}