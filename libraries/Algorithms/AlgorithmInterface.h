#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <Observer.h>


class AlgorithmInterface
{
    public:
        AlgorithmInterface() {};
        ~AlgorithmInterface() {};

        void init(Observer* obs) {m_obs = obs;}; 
        virtual void updateCmd() = 0;
        
        virtual void setLine(CoordLatLon a, CoordLatLon b) {};

        float getCmdRudder() {return m_cmd_rudder;};
        float getCmdSail() {return m_cmd_sail;};

    protected:
        Observer* m_obs = nullptr;
        float m_cmd_rudder = 0.5;
        float m_cmd_sail = 0.5;
};

#endif