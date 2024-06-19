#include <WindDirection.h>


WindDirection::WindDirection(){}


WindDirection::~WindDirection(){}


void WindDirection::init()
{
    m_raw_wind_direction = 0;
    m_wind_direction = 0;
}


void WindDirection::update()
{
    int vane_value = analogRead(WIND_DIRECTION_PIN);
    m_raw_wind_direction = map(vane_value, 0, 1023, 0, 360);
}


void WindDirection::setFilteredWindDirection(float wind_direction) {m_wind_direction = wind_direction;}


float WindDirection::getWindDirection() {return m_wind_direction;}
float WindDirection::getRawWindDirection() {return m_raw_wind_direction;}
