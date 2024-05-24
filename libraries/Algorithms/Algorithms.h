#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <Arduino.h>
#include <Config.h>
#include <Tools.h>
#include <AlgorithmInterface.h>


class LineFollowing : public AlgorithmInterface
{
    public:
        LineFollowing();
        ~LineFollowing();

        void updateCmd();

        void setLine(CoordLatLon a, CoordLatLon b);

    private:
        CoordXY m_a, m_b;
        int m_q;
};

#endif