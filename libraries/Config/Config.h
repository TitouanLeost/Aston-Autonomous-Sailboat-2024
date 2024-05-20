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
/*====WIND SPEED CONFIG====*/

#define SERIAL_WIND Serial1
#define WIND_SPEED_PIN 19

/*=========================*/
/////////////////////////////
/*=====OBSERVER CONFIG=====*/

#define YAW_FILTER 0.5

/*=========================*/

#endif