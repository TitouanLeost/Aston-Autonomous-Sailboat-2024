#include <Controller.h>


Controller::Controller()
{
    m_mr = new ServoMotor(SERVO_RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX);
    m_ms = new ServoMotor(SERVO_SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX);
    m_algo1 = new ALGO1();
    m_algo2 = new ALGO2();
}


Controller::~Controller()
{
    delete m_mr;
    delete m_ms;
    delete m_algo;
    delete m_algo1;
    delete m_algo2;
}


void Controller::init(Observer* obs)
{
    Serial.println("#########################");
    Serial.println("Initializing servo motors...");
    m_mr->init();
    m_ms->init();
    Serial.println("Servo motors initialized");
    Serial.println("######################### \n");

    Serial.println("#########################");
    Serial.println("Initializing algorithms...");   
    m_algo1->init(obs);
    m_algo2->init(obs); 
    Serial.println("Algorithms initialized");
    Serial.println("######################### \n");
}


void Controller::updateServos()
{
    if(m_update){
        m_algo->updateCmd();
        m_mr->setPercent(m_algo->getCmdRudder());
        m_ms->setPercent(m_algo->getCmdSail());
    }
}


int Controller::setAlgo(int type) 
{
    switch(type){
        case 1:
            m_algo = m_algo1;
            break;
        case 2:
            m_algo = m_algo2;
            break;
    }
    return type;
}


void Controller::setUpdate(bool update) {m_update = update;}


ServoMotor* Controller::mr() {return m_mr;}
ServoMotor* Controller::ms() {return m_ms;}
AlgorithmInterface* Controller::algo() {return m_algo;}
