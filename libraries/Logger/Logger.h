#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <SD.h>
#include <time.h>

#include <Config.h>
#include <Observer.h>
#include <Controller.h>
#include <RCReceiver.h>


/**************************************************************************
 * A class to handle the data logging.
 * This class allows to log data from the sensors of the boat.
**************************************************************************/
class Logger 
{
    public:
        Logger();
        ~Logger();

        /***********************************************************
         * Initialize the logger.
         * Checks the connection with the SD card and initializes
         * the observer, controller and RC receiver to use, 
         * then open the file.
         * @param obs The observer to log the data from.
         * @param ctrl The controller to log the data from.
         * @param rc The RC receiver to log the data from.
        ***********************************************************/
        void init(Observer* obs, Controller* ctrl, RCReceiver* rc);

        /***********************************************************
         * Update the logger.
         * Logs the data from the observer. The data are the time,
         * the yaw, the wind direction, the true wind angle,
         * the wind speed, the number of satellites, the latitude,
         * the longitude, the x and y coordinates, the rudder and
         * sail commands, and the status of the RC receiver.
        ***********************************************************/
        void update();


        void setUpdate(bool update);


        /***********************************************************
         * Open the file.
         * Generates the filename by calling the generateFilename()
         * method, opens the file and initializes it with the date 
         * and the time of the experimentation.
        ***********************************************************/
        void open();

        /***********************************************************
         * Close the file.
        ***********************************************************/
        void close();

    private:
        /***********************************************************
         * Generate the filename.
         * Generates the filename with the date and the time.
         * Only the day and month for the date and the hour and
         * minute for the time are used to keep a file name of
         * 8 caracters (maximum length allowed).
        ***********************************************************/
        void generateFilename();

        /***********************************************************
         * Write data to the file.
         * @param data The data to write.
        ***********************************************************/
        void write(float data);

        /***********************************************************
         * Write data to the file.
         * @param data The data to write.
        ***********************************************************/
        void write(unsigned long int data);

        /***********************************************************
         * Write data to the file.
         * @param data The data to write.
        ***********************************************************/
        void write(int data);

        /***********************************************************
         * Write data to the file.
         * @param data The data to write.
        ***********************************************************/
        void write(double data);

        /***********************************************************
         * Write data to the file.
         * @param msg The message to write.
        ***********************************************************/
        void write(String msg);

        Observer* m_obs;  ///< The observer to log the data from
        Controller* m_ctrl;  ///< The controller to log the data from
        RCReceiver* m_rc;  ///< The RC receiver to log the data from

        File m_file;  ///< The file to write the data
        String m_filename;  ///< The filename
        String m_date;  ///< The date of the experiment
        String m_time;  ///< The time of the experiment
        bool m_update = true;  ///< The update flag
};


#endif