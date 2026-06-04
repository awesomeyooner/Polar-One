#include "devices/timer_device.hpp"


using namespace status_utils;


TimerDevice::TimerDevice(TIM_HandleTypeDef* timer, int channel)
{
    m_timer = timer;
    m_channel = channel;

} // end of "TimerDevice(TIM_HandleTypeDef*, int)"


StatusCode TimerDevice::init()
{
    if(m_timer == nullptr)
        return StatusCode::FAILED;

    // Start the timer itself
    StatusCode base_status = HAL_TIM_Base_Init(m_timer) == HAL_OK ? StatusCode::OK : StatusCode::FAILED;

    // Start PWM on the specific channel
    StatusCode channel_status = HAL_TIM_PWM_Start(m_timer, m_channel) == HAL_OK ? StatusCode::OK : StatusCode::FAILED;
    
    return combine_statuses({base_status, channel_status});

} // end of "init()"


void TimerDevice::set_duty(double duty)
{
    if(m_channel == -1 || m_timer == nullptr)
        return;

    // Clamp from [0, 1]
    if(duty > 1)
        duty = 1;
    else if(duty < 0)
        duty = 0;

    int ARR = m_timer->Init.Period;

    // CCR / Pulse is just the fractional scale of ARR + 1
    int CCR = (double)(ARR + 1) * duty;

    __HAL_TIM_SET_COMPARE(m_timer, m_channel, CCR);

} // end of "set_duty(double)"


void TimerDevice::set_PSC(int psc)
{
    // htimx.Init.Prescaler
    __HAL_TIM_SET_PRESCALER(m_timer, psc);

} // end of "set_PSC(int)"


void TimerDevice::set_ARR(int arr)
{
    // htimx.Init.Period
    __HAL_TIM_SET_AUTORELOAD(m_timer, arr);

} // end of "set_ARR"


TIM_HandleTypeDef* TimerDevice::get_timer()
{
    return m_timer;

} // end of "get_timer()"


int TimerDevice::get_channel()
{
    return m_channel;

} // end of "get_channel()"


int TimerDevice::get_clock_freq()
{
    // Advanced timers use APB2, general ones use APB1
    int freq = is_APB2() ? HAL_RCC_GetPCLK2Freq() : HAL_RCC_GetPCLK1Freq();

    int prescalar = get_APB_prescaler();

    // A prescaler of 1 doubles the frequency for timers
    if(prescalar != RCC_HCLK_DIV1)
        freq *= 2;

    return freq;

} // end of "get_clock_freq()"


double TimerDevice::get_PWM_freq()
{
    int tim_clk = get_clock_freq();
    int psc = m_timer->Init.Prescaler;
    int arr = m_timer->Init.Period;

    return (double)tim_clk / (double)( (psc + 1) * (arr + 1) );

} // end of "get_PWM_freq"


bool TimerDevice::is_advanced_timer()
{
    TIM_TypeDef* instance = m_timer->Instance;

    // For F4 series, not sure about others
    return  instance == TIM1 || 
            instance == TIM8;

} // end of "is_advanced_timer()"


bool TimerDevice::is_APB2()
{
    TIM_TypeDef* instance = m_timer->Instance;

    // For F4 series, 9, 10, 11 are General Purpose but are on APB2
    return  is_advanced_timer() ||
            instance == TIM9 || 
            instance == TIM10 || 
            instance == TIM11;

} // end of "is_APB2()"


bool TimerDevice::is_APB1()
{
    // It can only be APB1 or APB2, so if it's not 2 then it must be 1
    return !is_APB2();

} // end of "is_APB1()"


int TimerDevice::get_APB_prescaler()
{
    RCC_ClkInitTypeDef clock_config;
    uint32_t flash_latency;

    HAL_RCC_GetClockConfig(&clock_config, &flash_latency);

    // Advanced timers use APB2
    if(is_APB2())
        return clock_config.APB2CLKDivider;
    else
        return clock_config.APB1CLKDivider;

} // end of "get_APB_prescaler"