#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Adafruit_PWMServoDriver.h>
#include <Config.h>


class ServoMotor
{
    public:
        ServoMotor(uint8_t pin, uint16_t pwm_min, uint16_t pwm_max);
        ~ServoMotor();

        void init();
        void setPWM(uint16_t pwm);
        void setPercent(float percent);

    private:
        Adafruit_PWMServoDriver* m_servo;
        uint16_t m_pwm_min, m_pwm_max;
        uint8_t m_pin;

};


#endif