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
    delay(1000);
    Serial.println("Servo motors initialized");
    Serial.println("######################### \n");

    Serial.println("#########################");
    Serial.println("Testing servo motors...");
    testServo();
    Serial.println("Servo motors tested");
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


void Controller::testServo()
{
    for(float i = 0.5; i <= 1.0; i += 0.1){
        m_mr->setPercent(i);
        m_ms->setPercent(i);
        delay(400);
    }
    for(float i = 1.0; i >= 0.0; i -= 0.1){
        m_mr->setPercent(i);
        m_ms->setPercent(i);
        delay(400);
    }
    m_mr->setPercent(0.5);
    m_ms->setPercent(0.5);
}
