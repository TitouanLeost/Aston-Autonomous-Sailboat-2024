#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <time.h>

#include <Config.h>
#include <Observer.h>


/**************************************************************************
 * A class to handle the data logging.
 * This class allow to log data from the sensors of the boat.
**************************************************************************/
class Logger 
{
    public:
        Logger();
        ~Logger();

        /********************************************************
         * Initialize the logger.
         * Check the connection with the SD card and initialize
         * the observer to use, then open the file.
         * @param obs The observer to log the data from.
        ********************************************************/
        void init(Observer* obs);

        /********************************************************
         * Update the logger.
         * Log the data from the observer. The data are the time,
         * the yaw, the wind direction, the true wind angle and
         * the wind speed.
        ********************************************************/
        void update();


        /********************************************************
         * Open the file.
         * Generate the filename, open the file and initialize
         * it with the date and the time.
        ********************************************************/
        void open();

        /********************************************************
         * Close the file.
        ********************************************************/
        void close();

    private:
        /********************************************************
         * Generate the filename.
         * Generate the filename with the date and the time.
         * Only the day and month for the date and the hour and
         * minute for the time are used to keep a file name of
         * 8 caracters (maximum length allowed).
        ********************************************************/
        void generateFilename();

        /********************************************************
         * Write data to the file.
         * @param data The data to write.
        ********************************************************/
        void write(float data);

        /********************************************************
         * Write data to the file.
         * @param data The data to write.
        ********************************************************/
        void write(unsigned long int data);

        /********************************************************
         * Write data to the file.
         * @param data The data to write.
        ********************************************************/
        void write(int data);

        /********************************************************
         * Write data to the file.
         * @param data The data to write.
        ********************************************************/
        void write(double data);

        /********************************************************
         * Write data to the file.
         * @param msg The message to write.
        ********************************************************/
        void write(String msg);

        Observer* m_obs;  ///< The observer to log the data from

        File m_file;  ///< The file to write the data
        String m_filename;  ///< The filename
        String m_date;  ///< The date of the experiment
        String m_time;  ///< The time of the experiment
};


#endif