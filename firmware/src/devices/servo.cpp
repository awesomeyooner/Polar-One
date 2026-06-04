#include "devices/servo.hpp"


Servo::Servo(TIM_HandleTypeDef* timer, int channel)
{
    m_timer = timer;
    m_channel = channel;

} // end of "Servo(TIM_HandleTypeDef*, int)"


void Servo::init()
{
    if(m_timer == nullptr)
        return;

    HAL_TIM_Base_Start(m_timer);
    HAL_TIM_PWM_Start(m_timer, m_channel);

} // end of "init()"


void Servo::set_duty_cycle(double duty)
{
    if(m_channel == -1)
        return;

    set_duty_cycle(duty, m_channel);

} // end of "set_duty_cycle(double)"


void Servo::set_duty_cycle(double duty, int pin)
{
    if(duty > 1)
        duty = 1;
    else if(duty < 0)
        duty = 0;

    int ARR = m_timer->Init.Period;
    int CCR = (double)(ARR + 1) * duty;

    __HAL_TIM_SET_COMPARE(m_timer, pin, CCR);

} // end of "set_duty_cycle(double, int)"