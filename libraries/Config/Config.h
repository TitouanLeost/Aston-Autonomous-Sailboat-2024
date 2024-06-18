#ifndef CONFIG_H
#define CONFIG_H


/*======GENERAL CONFIG=====*/

#define EARTH_RADIUS 6371000

#define REF_LAT 52.486252  // Reference latitude
#define REF_LON -1.889658  // Reference longitude

/*=========================*/
/////////////////////////////
/*======MISSION CONFIG=====*/

#define ALGO1 LineFollowing  // Algorithm used to go from waypoint to waypoint (type 1)
#define ALGO2 StationKeeping  // Algorithm used when a waypoint is reached (type 2)
#define NB_WP 3  // Number of waypoints
// List of waypoints (latitude, longitude)
#define WP { {52.486599, -1.889232}, {52.486302, -1.889515}, {52.486382, -1.889144} }
#define WP_RADIUS 10  // Radius of the waypoint to validate it
#define ALGO2_DURATION 10  // Duration (in seconds) of the type 2 algorithm before going to the next waypoint

/*=========================*/
/////////////////////////////
/*====RCRECEIVER CONFIG====*/

#define RUDDER_CH_PIN 3  // Pin for the rudder channel
#define SAIL_CH_PIN 2  // Pin for the sail channel
#define NB_CHANNELS 2  // Number of channels
enum RC_CHANNELS {RUDDER_CH, SAIL_CH};
#define RUDDER_OFFSET_MIN 1079  // Minimum offset for the rudder
#define RUDDER_OFFSET_MAX 1975  // Maximum offset for the rudder
#define SAIL_OFFSET_MIN 1057  // Minimum offset for the sail
#define SAIL_OFFSET_MAX 1878  // Maximum offset for the sail
#define PULSE_FILTER 0.95  // Coefficient of the filter for the pulse

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

#define YAW_FILTER 0.7  // Coefficient of the filter for the yaw
#define WIND_DIRECTION_FILTER 0.8  // Coefficient of the filter for the wind direction

/*=========================*/
/////////////////////////////
/*======CMPS12 CONFIG======*/

#define SERIAL_CMPS Serial3  // Serial port for the CMPS
#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15
#define CMPS_CALIBRATION_STATUS 0x24

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
#define RUDDER_PWMMIN 200  // Minimum PWM for the rudder servo
#define RUDDER_PWMMAX 380  // Maximum PWM for the rudder servo

#define SERVO_SAIL_PIN 1  // Pin for the sail servo
#define SAIL_PWMMIN 245  // Minimum PWM for the sail servo
#define SAIL_PWMMAX 330  // Maximum PWM for the sail servo

/*=========================*/
/////////////////////////////
/*======LOGGER CONFIG======*/

#define SD_PIN 53  // Pin for the SD card

/*=========================*/

#endif