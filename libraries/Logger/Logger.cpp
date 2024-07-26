#include <Logger.h>


Logger::Logger() {}


Logger::~Logger() {}


void Logger::init(Observer* obs, Controller* ctrl, RCReceiver* rc)
{
    if(!SD.begin(SD_PIN)){
        Serial.println("SD card initialization failed");
        while(1);
    }

    m_obs = obs;
    m_ctrl = ctrl;
    m_rc = rc;

    m_update = true;
    m_last_time = millis();

    open();
}


void Logger::update()
{
    if((!m_update) || ((millis() - m_last_time) < LOG_INTERVAL))
        return;
        
    unsigned long int time = millis();
    float yaw = m_obs->cmps()->getYaw();
    float yaw_raw = m_obs->cmps()->getYawRaw();
    float wind_direction = m_obs->wd()->getWindDirection();
    float wind_direction_raw = m_obs->wd()->getRawWindDirection();
    float true_wind_direction = m_obs->getTrueWindAngle();
    float wind_speed = m_obs->ws()->getWindSpeed();
    int satellites = m_obs->gps()->getSatellites();
    double course = m_obs->gps()->getCourse();
    double speed = m_obs->gps()->getSpeed();
    CoordLatLon latlon = m_obs->gps()->getCoordLatLon();
    CoordXY xy = m_obs->gps()->getCoordXY();
    float rudder_cmd = m_ctrl->algo()->getCmdRudder();
    float sail_cmd = m_ctrl->algo()->getCmdSail();
    bool rc_is_receiving = m_rc->status();

    write(time); write(",");
    write(yaw); write(",");
    write(yaw_raw); write(",");
    write(wind_direction); write(",");
    write(wind_direction_raw); write(",");
    write(true_wind_direction); write(",");
    write(wind_speed); write(",");
    write(satellites); write(",");
    write(course); write(",");
    write(speed); write(",");
    write(latlon.lat); write(",");
    write(latlon.lon); write(",");
    write(xy.x); write(",");
    write(xy.y); write(",");
    write(rudder_cmd); write(",");
    write(sail_cmd); write(",");
    write(rc_is_receiving); write("\n");
 
    m_file.flush();
}


void Logger::open()
{
    generateFilename();
    CoordLatLon wp[NB_WP] = WP;

    Serial.println("#########################");
    Serial.print("Opening file: "); Serial.println(m_filename);
    Serial.println("#########################\n");

    SD.remove(m_filename);
    m_file = SD.open(m_filename, FILE_WRITE);

    write(m_date); write("_"); write(m_time); write("\n");
    write("REF_LAT, REF_LON\n");
    write(REF_LAT); write(","); write(REF_LON); write("\n");
    write("Waypoints (nb, radius):\n");
    write(NB_WP); write(","); write(WP_RADIUS); write("\n");
    write("Waypoints (lat, lon):\n");
    for(int i = 0; i < NB_WP; i++){
        write(wp[i].lat); write(","); write(wp[i].lon); write("\n");
    }
    write("Time (ms), Yaw Filtered (deg), Yaw Raw (deg), Wind Direction Filtered (deg), ");
    write("Wind Direction Raw (deg), True Wind Direction (deg), Wind Speed (kph), ");
    write("Satellites, Course (deg), Speed (kph), Latitude (deg), Longitude (deg), X (m), Y (m), ");
    write("Rudder Cmd (%), Sail Cmd (%), RC Reception\n");
}


void Logger::close()
{
    m_file.flush();
    m_file.close();
    m_filename = "";
    m_update = false;
}


void Logger::generateFilename()
{
    m_date = m_obs->gps()->getDate();
    String date = m_date.substring(0, m_date.length() - 2);  // Remove year
    m_time = m_obs->gps()->getTime();
    String time = m_time.substring(0, m_time.length() - 2);  // Remove seconds
    // m_filename += date;
    // m_filename += time;
    // m_filename += ".TXT";
    m_filename = "TEST.TXT";
}


void Logger::write(float data) {m_file.print(data, 3);}
void Logger::write(unsigned long int data) {m_file.print(data);}
void Logger::write(int data) {m_file.print(data);}
void Logger::write(double data) {m_file.print(data, 6);}
void Logger::write(String msg) {m_file.print(msg);}