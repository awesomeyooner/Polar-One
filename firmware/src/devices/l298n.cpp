#include "devices/l298n.hpp"


L298N::L298N(TIM_HandleTypeDef* timer, int in1, int in2)
{
    m_timer = timer;
    m_in1 = in1;
    m_in2 = in2;

} // end of "L298N(TIM_HandleTypeDef*, int, int)"


void L298N::init()
{
    if(m_timer == nullptr)
        return;

    HAL_TIM_Base_Start(m_timer);
    HAL_TIM_PWM_Start(m_timer, m_in1);
    HAL_TIM_PWM_Start(m_timer, m_in2);
}


void L298N::set_percent(double percent)
{
    if(percent > 1)
        percent = 1;
    else if(percent < -1)
        percent = -1;

    int duty = abs(percent * 100);

    if(percent > 0)
    {
        set_duty_cycle(duty, m_in1);
        set_duty_cycle(0, m_in2);
    }
    else if(percent < 0)
    {
        set_duty_cycle(0, m_in1);
        set_duty_cycle(duty, m_in2);
    }
    else // percent == 0
    {
        set_duty_cycle(0, m_in1);
        set_duty_cycle(0, m_in2);
    }

} // end of "set_percent(double)"


void L298N::set_duty_cycle(int duty, int pin)
{
    if(duty > 100)
        duty = 100;
    else if(duty < 0)
        duty = 0;

    int ARR = m_timer->Init.Period;
    int CCR = (double)(ARR + 1) * (double)(duty / 100.0);

    __HAL_TIM_SET_COMPARE(m_timer, pin, CCR);

} // end of "set_duty_cycle(int, int)"