#include <Controller.h>


Controller::Controller()
{
    m_mr = new ServoMotor(SERVO_RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX);
    m_ms = new ServoMotor(SERVO_SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX);
}


Controller::~Controller()
{
    delete m_mr;
    delete m_ms;
}


void Controller::init()
{
    Serial.println("#########################");
    Serial.println("Initializing servo motors...");
    m_mr->init();
    m_ms->init();
    Serial.println("Servo motors initialized");
    Serial.println("######################### \n");
}


void Controller::updateServos()
{
    // TODO
}


ServoMotor* Controller::mr() {return m_mr;}
ServoMotor* Controller::ms() {return m_ms;}
