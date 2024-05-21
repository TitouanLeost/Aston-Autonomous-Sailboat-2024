#ifndef CONFIG_H
#define CONFIG_H


/*======GENERAL CONFIG=====*/

#define EARTH_RADIUS 6371000

#define REF_LON 0.0
#define REF_LAT 0.0

/*=========================*/
/////////////////////////////
/*======CMPS12 CONFIG======*/

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15
#define CMPS_RX 10
#define CMPS_TX 11

/*=========================*/
/////////////////////////////
/*========GPS CONFIG=======*/

#define SERIAL_GPS Serial2

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

#define SERIAL_WIND Serial1
#define WIND_SPEED_PIN 19
#define WIND_DIRECTION_PIN A14

/*=========================*/
/////////////////////////////
/*=====OBSERVER CONFIG=====*/

#define YAW_FILTER 0.5

/*=========================*/
/////////////////////////////
/*=======SERVO CONFIG======*/

#define SERVO_FREQ 50

#define SERVO_RUDDER_PIN 0
#define RUDDER_PWMMIN 220
#define RUDDER_PWMMAX 420

#define SERVO_SAIL_PIN 1
#define SAIL_PWMMIN 340
#define SAIL_PWMMAX 460

/*=========================*/

#endif