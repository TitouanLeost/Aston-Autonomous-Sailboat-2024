#include <Logger.h>


Logger::Logger(){}


Logger::~Logger()
{
    close();
}


void Logger::init(Observer* obs)
{
    // SD.begin(SD_PIN);
    if(!SD.begin(SD_PIN))
    {
        Serial.println("SD card initialization failed");
        return;
    }
    SD.mkdir("LOG");

    m_obs = obs;
    open();
}


void Logger::update()
{
    write(m_obs->cmps()->getYaw());

    m_file.print("\n\r");
    
    m_file.flush();
}


String Logger::open()
{
  m_filename = "LOG/test.txt";
  m_file = SD.open(m_filename, FILE_WRITE);

  return m_filename;
}


void Logger::close()
{
    m_file.flush();
    m_file.close();
    m_filename = "";
}


void Logger::write(float data)
{
    m_file.print(data, 5);
}