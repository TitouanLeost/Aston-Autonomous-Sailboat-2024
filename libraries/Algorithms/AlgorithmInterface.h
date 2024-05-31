#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <Observer.h>


/**************************************************************************
 * A base class to handle all algorithms class.
 * This class contain basic functions for all algorithms to use.
**************************************************************************/
class AlgorithmInterface
{
    public:
        AlgorithmInterface() {};
        ~AlgorithmInterface() {};


        /*************************************************************
         * Initialize the algorithm.
         * This function initialize the algorithm with the observer.
         * @param obs A pointer to the observer used
        *************************************************************/
        void init(Observer* obs) {m_obs = obs;}; 
        virtual void updateCmd() = 0;
        
        virtual void setLine(CoordLatLon a, CoordLatLon b) {};


        /*************************************************************
         * Get the rudder command.
         * @return The rudder command (0.0 to 1.0)
        *************************************************************/
        float getCmdRudder() {return m_cmd_rudder;};

        /*************************************************************
         * Get the sail command.
         * @return The sail command (0.0 to 1.0)
        *************************************************************/
        float getCmdSail() {return m_cmd_sail;};

    protected:
        Observer* m_obs = nullptr;  ///< The observer used
        float m_cmd_rudder = 0.5;  ///< The rudder command (0.0 to 1.0)
        float m_cmd_sail = 0.5;  ///< The sail command (0.0 to 1.0)
};

#endif