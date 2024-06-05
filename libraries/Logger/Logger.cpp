#include <Logger.h>


Logger::Logger(){}


Logger::~Logger()
{
    close();
}


void Logger::init(Observer* obs)
{
    if(!SD.begin(SD_PIN)){
        Serial.println("SD card initialization failed");
        while(1);
    }
    SD.mkdir("LOG");

    m_obs = obs;
    open();
}


void Logger::update()
{
    unsigned long int time = millis();
    float yaw = m_obs->cmps()->getYaw();
    float yaw_raw = m_obs->cmps()->getYawRaw();
    float wind_direction = m_obs->wd()->getWindDirection();
    float wind_direction_raw = m_obs->wd()->getRawWindDirection();
    float true_wind_direction = m_obs->getTrueWindAngle();
    float wind_speed = m_obs->ws()->getWindSpeed();

    write(time); write(",");
    write(yaw); write(",");
    write(yaw_raw); write(",");
    write(wind_direction); write(",");
    write(wind_direction_raw); write(",");
    write(true_wind_direction); write(",");
    write(wind_speed); write("\n");
    
    m_file.flush();
}


void Logger::open()
{
    generateFilename();

    Serial.print("Opening file: "); Serial.println(m_filename);

    SD.remove(m_filename);
    m_file = SD.open(m_filename, FILE_WRITE);

    write(m_date); write("_"); write(m_time); write("\n");
    write("Time (ms), Yaw Filtered (deg), Yaw Raw (deg), Wind Direction Filtered (deg), ");
    write("Wind Direction Raw (deg), True Wind Direction (deg), Wind Speed (kph)\n");
}


void Logger::close()
{
    m_file.flush();
    m_file.close();
    Serial.println("File closed");
    m_filename = "";
}


void Logger::generateFilename()
{
    m_date = m_obs->gps()->getDate();
    String date = m_date.substring(0, m_date.length() - 2);  // Remove year
    m_time = m_obs->gps()->getTime();
    String time = m_time.substring(0, m_time.length() - 2);  // Remove seconds
    m_filename = "LOG/";
    m_filename += date;
    m_filename += time;
    m_filename += ".TXT";
}


void Logger::write(float data) {m_file.print(data, 3);}
void Logger::write(unsigned long int data) {m_file.print(data);}
void Logger::write(String msg) {m_file.print(msg);}