#ifndef CONFIG_H
#define CONFIG_H


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
/*=====OBSERVER CONFIG=====*/

#define YAW_FILTER 0.5

/*=========================*/

#endif