#include <WindSpeed.h>


WindSpeed::WindSpeed(){}


WindSpeed::~WindSpeed(){}


void WindSpeed::init()
{
    m_nb_rotations = 0;
    m_contact_time = 0;
    m_average_time = millis();
    m_wind_speed = 0;
}


void WindSpeed::update()
{
    if((millis() - m_average_time) > 5000)  // No rotations for more than 5 seconds
    {
        m_wind_speed = 0;
        m_nb_rotations = 0;
        m_average_time = millis();
    }
}


void WindSpeed::rotation()
{
    if((millis() - m_contact_time) > 15)
    {
        m_nb_rotations++;
        m_contact_time = millis();
    }

    if((millis() - m_average_time) > 3000)
    {
        m_wind_speed = m_nb_rotations * 0.75 * 1.609;  // Speed in kph
        m_nb_rotations = 0;
        m_average_time = millis();
    }
}


double WindSpeed::getWindSpeed() {return m_wind_speed;}