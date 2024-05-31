#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <time.h>

#include <Config.h>
#include <Observer.h>


class Logger 
{
    public:
        Logger();
        ~Logger();

        void init(Observer* obs);
        void update();

        String open();
        void close();

        void write(float data);

    private:
        Observer* m_obs;

        File m_file;
        String m_filename;
};


#endif