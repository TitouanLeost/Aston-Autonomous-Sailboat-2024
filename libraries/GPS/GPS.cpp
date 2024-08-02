#include <GPS.h>


GPS::GPS() {}


GPS::~GPS() {}


void GPS::init()
{
    Serial.println(" -> Initializing GPS...");
    
    SERIAL_GPS.begin(9600);
    while(SERIAL_GPS.available() == 0);
    while(m_gps.sentencesWithFix() <= 10)
        update();

    Serial.println(" => GPS initialized");
}


void GPS::update()
{
    while(SERIAL_GPS.available() > 0)
        m_gps.encode(SERIAL_GPS.read());
}


double GPS::getLat() {return m_gps.location.isValid() ? m_gps.location.lat() : 99999;}
double GPS::getLon() {return m_gps.location.isValid() ? m_gps.location.lng() : 99999;}

double GPS::getCourse() {return ((m_gps.course.isValid()) && (m_gps.course.deg() <= 360)) ? m_gps.course.deg() : -1;}
double GPS::getSpeed() {return m_gps.speed.isValid() ? m_gps.speed.kmph() : 0;}

int GPS::getSatellites() {return m_gps.satellites.value();}


String GPS::getDate(){
    if(!m_gps.date.isValid())
        return "-1";

    uint32_t date = m_gps.date.value();
    String dateStr = String(date);
    if (dateStr.length() == 5)
        dateStr = "0" + dateStr;

    return dateStr;  
}


String GPS::getTime(){
    if(!m_gps.time.isValid())
        return "-1";

    String timeStr;
    String h = String(m_gps.time.hour());
    String m = String(m_gps.time.minute());
    String s = String(m_gps.time.second());

    timeStr = (h.length() == 1 ? "0" + h : h) + (m.length() == 1 ? "0" + m : m) + (s.length() == 1 ? "0" + s : s);
    return timeStr;
}


CoordLatLon GPS::getCoordLatLon()
{
    CoordLatLon coord;
    coord.lat = getLat();
    coord.lon = getLon();
    return coord;
}


CoordXY GPS::getCoordXY()
{
    CoordXY coord;
    coord = latLonToXY(getCoordLatLon());
    return coord;
}
