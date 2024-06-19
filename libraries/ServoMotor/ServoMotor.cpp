#include <ServoMotor.h>


ServoMotor::ServoMotor(uint8_t pin, uint16_t pwm_min, uint16_t pwm_max)
{
    m_servo = new Adafruit_PWMServoDriver();
    m_pwm_min = pwm_min;
    m_pwm_max = pwm_max;
    m_pin = pin;
}


ServoMotor::~ServoMotor()
{
    delete m_servo;
}


void ServoMotor::init()
{
    m_servo->begin();
    m_servo->setPWMFreq(SERVO_FREQ);
    setPWM((int)(m_pwm_max + m_pwm_min)/2);
}


void ServoMotor::setPWM(uint16_t pwm)
{
    if(pwm < m_pwm_min)
        pwm = m_pwm_min;
    else if(pwm > m_pwm_max)
        pwm = m_pwm_max;

    m_servo->setPWM(m_pin, 0, pwm);
}


void ServoMotor::setPercent(float percent)
{
    if(percent < 0.0)
        percent = 0.0;
    else if(percent > 1.0)
        percent = 1.0;

    uint16_t pwm = (int) (m_pwm_max - m_pwm_min)*percent + m_pwm_min;
    setPWM(pwm);
}
