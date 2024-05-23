#include <Controller.h>


ControllerLF::ControllerLF()
{
    m_algo = new LineFollowing();
}


ControllerLF::~ControllerLF()
{
    delete m_algo;
}


void ControllerLF::init()
{
    Serial.println("#########################");
    Serial.println("Initializing servo motors...");
    m_mr->init();
    m_ms->init();
    Serial.println("Servo motors initialized");
    Serial.println("######################### \n");
}


void ControllerLF::updateServos()
{
    m_algo->updateCmd();
    m_mr->setPercent(m_algo->getCmdRudder());
    m_ms->setPercent(m_algo->getCmdSail());
}
