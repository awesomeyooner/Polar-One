#ifndef SERVO_HPP
#define SERVO_HPP


#include "tim.h"


class Servo
{

    public:

        Servo(TIM_HandleTypeDef* timer, int channel);

        void init();

        void set_duty_cycle(double duty);

    private:

        TIM_HandleTypeDef* m_timer = nullptr;

        int m_channel = -1;

        void set_duty_cycle(double duty, int pin);

}; // class Servo

#endif // SERVO_HPP