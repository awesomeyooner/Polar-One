#include "devices/servo.hpp"


Servo::Servo(TIM_HandleTypeDef* timer, int channel)
    : TimerDevice(timer, channel)
{} // end of "Servo(TIM_HandleTypeDef*, int)"


void Servo::set_ranges(double min_duty, double max_duty, double angle_range)
{
    m_min_duty = min_duty;
    m_max_duty = max_duty;
    m_angle_range = angle_range;

} // end of "set_range(double, double, double)"


void Servo::set_lower_limit(double limit)
{
    m_lower_angle_limit = limit;
     
} // end of "set_lower_limit(double)"


void Servo::set_upper_limit(double limit)
{
    m_upper_angle_limit = limit;

} // end of "set_upper_limit(double)"


void Servo::set_angle(double radians)
{
    radians = get_clamped_angle(radians);

    // If the range is 270 and 90 is requested, the duty cycle would be  
    double duty = (get_duty_per_radian() * radians) + m_min_duty;

    set_duty(duty);

} // end of "set_angle(double)"


double Servo::get_angle()
{
    double duty = get_duty();
    double radians_per_duty = 1 / get_duty_per_radian();
    
    return duty * radians_per_duty;

} // end of "get_angle()"


double Servo::get_duty_per_radian()
{
    // The amount difference to go from min angle to max angle
    double duty_range = m_max_duty - m_min_duty;

    // 1 `duty_range` to go 1 `m_angle_range`,
    double duty_per_radian = duty_range / m_angle_range;

    return duty_per_radian;

} // end of "get_duty_per_radian()"


double Servo::get_clamped_angle(double radians)
{
    if(m_upper_angle_limit != -1 && radians > m_upper_angle_limit)
        return m_upper_angle_limit;
    else if(m_lower_angle_limit != -1 && radians < m_lower_angle_limit)
        return m_lower_angle_limit;
    else
        return radians;
}


void Servo::stop()
{
    set_duty(0);

} // end of "stop()"