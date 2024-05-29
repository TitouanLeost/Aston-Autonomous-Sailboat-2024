#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Adafruit_PWMServoDriver.h>
#include <Config.h>


/**********************************************************************************
 * A class to handle a servo motor.
 * This class allow to control a servo motor with a PWM signal between 0 and 4096
 * or a float between 0.0 and 1.0.
**********************************************************************************/
class ServoMotor
{
    public:
        /******************************************************************
         * Constructor of the class.
         * @param pin The pin of the servo motor
         * @param pwm_min The minimum PWM value of the servo motor
         * @param pwm_max The maximum PWM value of the servo motor
        *******************************************************************/
        ServoMotor(uint8_t pin, uint16_t pwm_min, uint16_t pwm_max);
        ~ServoMotor();

        /******************************************************************
         * Initialize the servo motor.
         * This function set the frequence of the motor and set its PWM to
         * its mean value.
        *******************************************************************/
        void init();

        /******************************************************************
         * Set the PWM of the servo motor.
         * @param pwm The PWM value to set to the servo motor
        *******************************************************************/
        void setPWM(uint16_t pwm);

        /******************************************************************
         * Set the PWM of the servo motor with a percent.
         * @param percent The percent (between 0.0 and 1.0) of the PWM to 
         * set to the servo motor
        *******************************************************************/
        void setPercent(float percent);

    private:
        Adafruit_PWMServoDriver* m_servo;  ///< The servo motor object
        uint16_t m_pwm_min;  ///< The minimum PWM value of the servo motor
        uint16_t m_pwm_max;  ///< The maximum PWM value of the servo motor
        uint8_t m_pin;  ///< The pin of the servo motor

};


#endif