#ifndef CONTROLALGORITHM_H
#define CONTROLALGORITHM_H

#include <Observer.h>


class ControlAlgorithm
{
    public:
        ControlAlgorithm() {};
        ~ControlAlgorithm() {};

        void init(Observer* obs) {m_obs = obs;}; 
        virtual void updateCmd() = 0;

        float getCmdRudder() {return m_cmd_rudder;};
        float getCmdSail() {return m_cmd_sail;};

    protected:
        Observer* m_obs = nullptr;
        float m_cmd_rudder = 0.5;
        float m_cmd_sail = 0.5;
};

#endif