#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <Arduino.h>

#include <Config.h>
#include <Tools.h>
#include <AlgorithmInterface.h>


/*********************************************************************************
 * A class to handle the line following algorithm.
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
         * This function update the command to send to the boat
         * using a line following algorithm.
        ********************************************************/
        void updateCmd();


        /********************************************************
         * Set the line to follow.
         * This function set the line to follow with two points.
         * @param a The starting point of the line
         * @param b The ending point of the line
        ********************************************************/
        void setLine(CoordLatLon a, CoordLatLon b);

    private:
        CoordXY m_a;  ///< The starting point of the line
        CoordXY m_b;  ///< The ending point of the line
        int m_q;  ///< The sign of the error
};

#endif