#ifndef CONFIG_H
#define CONFIG_H


/*======GENERAL CONFIG=====*/

#define EARTH_RADIUS 6371000

#define REF_LON 0.0
#define REF_LAT 0.0

/*=========================*/
/////////////////////////////
/*====RCRECEIVER CONFIG====*/

#define RUDDER_CH_PIN 3  // Pin for the rudder channel
#define SAIL_CH_PIN 2  // Pin for the sail channel
#define NB_CHANNELS 2  // Number of channels
enum RC_CHANNELS {RUDDER_CH, SAIL_CH};
#define RUDDER_OFFSET_MIN 1076  // Minimum offset for the rudder
#define RUDDER_OFFSET_MAX 1979  // Maximum offset for the rudder
#define SAIL_OFFSET_MIN 1051  // Minimum offset for the sail
#define SAIL_OFFSET_MAX 1873  // Maximum offset for the sail

/*=========================*/
/////////////////////////////
/*====SUPERVISOR CONFIG====*/

#define CONTROLLER ControllerLF  // Line Following controller
#define NB_WP 3  // Number of waypoints
// List of waypoints (latitude, longitude)
#define WP { {52.485, 1.889709594213}, {52.4854920485, 1.889248254262}, {52.4844804397, 1.890610816442} }
#define WP_RADIUS 10  // Radius of the waypoint to validate it

/*=========================*/
/////////////////////////////
/*====ALGORITHMS CONFIG====*/

#define ANGLE_RUDDER_MAX M_PI/4  // Maximum angle of the rudder
#define ANGLE_SAIL_MAX M_PI/2  // Maximum angle of the sail

#define R 50  // Cutoff distance from the line
#define GAMMA M_PI/4  // Incidence angle
#define ZETA M_PI/4  // Close haul angle
#define BETA 0.3

/*=========================*/
/////////////////////////////
/*=====OBSERVER CONFIG=====*/

#define YAW_FILTER 0.5  // Coefficient of the filter for the yaw
#define WIND_DIRECTION_FILTER 0.5  // Coefficient of the filter for the wind direction

/*=========================*/
/////////////////////////////
/*======CMPS12 CONFIG======*/

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15
#define CMPS_CALIBRATION_STATUS 0x24
#define CMPS_RX 10  // RX pin for the CMPS
#define CMPS_TX 11  // TX pin for the CMPS

/*=========================*/
/////////////////////////////
/*========GPS CONFIG=======*/

#define SERIAL_GPS Serial2  // Serial port for the GPS

struct CoordLatLon
{
    double lat;
    double lon;
};

struct CoordXY
{
    double x;
    double y;
};

/*=========================*/
/////////////////////////////
/*====ANEMOMETER CONFIG====*/

#define SERIAL_WIND Serial1  // Serial port for the anemometer
#define WIND_SPEED_PIN 19  // Pin for the wind speed sensor
#define WIND_DIRECTION_PIN A14  // Pin for the wind direction sensor

/*=========================*/
/////////////////////////////
/*=======SERVO CONFIG======*/

#define SERVO_FREQ 50

#define SERVO_RUDDER_PIN 0  // Pin for the rudder servo
#define RUDDER_PWMMIN 220  // Minimum PWM for the rudder servo
#define RUDDER_PWMMAX 420  // Maximum PWM for the rudder servo

#define SERVO_SAIL_PIN 1  // Pin for the sail servo
#define SAIL_PWMMIN 340  // Minimum PWM for the sail servo
#define SAIL_PWMMAX 460  // Maximum PWM for the sail servo

/*=========================*/
/////////////////////////////
/*======LOGGER CONFIG======*/

#define SD_PIN 53  // Pin for the SD card

/*=========================*/

#endif