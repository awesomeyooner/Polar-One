#include "robot_hardware/hardware_manager.hpp"


using namespace std;
using namespace status_utils;


SerialInterface& HardwareManager::get_serial_port()
{
    return m_serial_port;

} // end of "get_serial_port()"


StatusCode HardwareManager::init(string field_name, string description)
{
    return m_serial_port.init_field(field_name, description);
    
} // end of "init(string, string)"


void HardwareManager::close()
{
    m_serial_port.close();

} // end of "close()"

StatusCode HardwareManager::set_servo(double radians)
{
    return m_serial_port.write_double(
        REG_SERVO_POSITION,
        radians,
        true // Acknowledge
    );

} // end of "set_servo(double)"


StatusCode HardwareManager::set_servo_from_center(double radians)
{
    return set_servo(m_servo_center + radians);
    
} // end of "set_servo_from_center(double)"


StatusCode HardwareManager::set_servo_percent_from_center(double percent)
{
    double center_to_bound = 0;

    // If positive
    // Center to bound uses upper bound
    if(percent > 0)
        center_to_bound = m_servo_upper_bound - m_servo_center;
    // If negative
    // Center to bound uses lower bound
    else if(percent < 0)
        center_to_bound = m_servo_center - m_servo_lower_bound;

    double angle = (percent * center_to_bound) + m_servo_center;

    return set_servo(angle);

} // end of "set_servo_percent_from_center(double)"


StatusCode HardwareManager::set_motor(double percent)
{
    return m_serial_port.write_double(
        REG_MOTOR_PERCENT,
        percent,
        true // Acknowledge
    );

} // end of "set_motor(double)"


StatusCode HardwareManager::set_servo_bounds(double lower_radians, double upper_radians)
{
    m_servo_lower_bound = lower_radians;
    m_servo_upper_bound = upper_radians;

    StatusCode lower_status = m_serial_port.write_double(REG_SERVO_LOWER_LIMIT, lower_radians, true);
    StatusCode upper_status = m_serial_port.write_double(REG_SERVO_UPPER_LIMIT, upper_radians, true);

    return combine_statuses({lower_status, upper_status});

} // end of "set_servo_bounds(double, double)"


void HardwareManager::set_servo_center(double center)
{
    m_servo_center = center;

} // end of "set_servo_center(double)"
