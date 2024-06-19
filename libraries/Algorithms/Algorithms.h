#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <Arduino.h>

#include <Config.h>
#include <Tools.h>
#include <AlgorithmInterface.h>


/*********************************************************************************
 * A class to handle a simple line following algorithm.
 * This class allows to follow a line with the boat. The algorithm is based on
 * the use of potential fields.
*********************************************************************************/
class LineFollowing : public AlgorithmInterface
{
    public:
        LineFollowing();
        ~LineFollowing();


        /********************************************************
         * Update the command.
         * This function updates the command to send to the boat
         * using a line following algorithm.
        ********************************************************/
        void updateCmd();

        /********************************************************
         * Update the waypoint.
         * This function updates the waypoint to reach.
         * @param a The previous waypoint
         * @param b The new waypoint to reach
        ********************************************************/
        void updateWaypoint(CoordLatLon a, CoordLatLon b);

    private:
        /********************************************************
         * Set the line to follow.
         * This function sets the line to follow with two points.
         * @param a The starting point of the line
         * @param b The ending point of the line
        ********************************************************/
        void setLine(CoordLatLon a, CoordLatLon b);

        CoordXY m_a;  ///< The starting point of the line
        CoordXY m_b;  ///< The ending point of the line
        int m_q;  ///< The sign of the error
};


/*********************************************************************************
 * A class to handle a station keeping algorithm.
 * This class allows to keep the boat at a fixed position.
*********************************************************************************/
class StationKeeping : public AlgorithmInterface
{
    // TO DO
    public:
        StationKeeping();
        ~StationKeeping();

        void updateCmd();
};


/*********************************************************************************
 * A class which is used when you do not want to have a type 2 algorithm.
*********************************************************************************/
class NoAlgorithm : public AlgorithmInterface
{
    public:
        NoAlgorithm(){};
        ~NoAlgorithm(){};

        void updateCmd(){};
};

#endif