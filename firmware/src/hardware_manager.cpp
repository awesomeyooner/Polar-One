#include "hardware_manager.hpp"


using namespace status_utils;
using namespace math;
using namespace std;


void HardwareManager::init()
{
    m_motor.init();
    m_servo.init();

    m_servo.set_ranges(0.035, 0.135, degrees_to_radians(270));
    m_servo.set_lower_limit(degrees_to_radians(120));
    m_servo.set_upper_limit(degrees_to_radians(150));

} // end of init();


void HardwareManager::update()
{
    if(!System::is_OK())
    {
        stop();
    }

} // end of "update()"


void HardwareManager::stop()
{
    m_motor.stop();
    m_servo.stop();

} // end of "stop()"


void HardwareManager::add_registers()
{
    RegisterManager::add_command(
        REG_SET_SERVO,
        sizeof(double),
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            double data = ByteConverter::bytes_to_double(bytes);

            System::feed();

            if(System::is_OK())
                m_servo.set_angle(data);
            else
                m_servo.stop();

            return StatusCode::OK;
        }
    ); // REG_SET_SERVO

    RegisterManager::add_command(
        REG_SET_MOTOR,
        sizeof(double),
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            double data = ByteConverter::bytes_to_double(bytes);

            System::feed();

            if(System::is_OK())
                m_motor.set_percent(data);
            else
                m_motor.stop();

            return StatusCode::OK;
        }
    ); // REG_SET_MOTOR

    RegisterManager::add_command(
        REG_SET_SERVO_LOWER_BOUND,
        sizeof(double),
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            ActionManager::add(Action::run_once(
                [bytes] -> void
                {
                    double data = ByteConverter::bytes_to_double(bytes);
                    m_servo.set_lower_limit(data);
                    
                    // Send Acknowledge Bytes
                    Serial.transmit_bytes(bytes);
                }
            ));

            return StatusCode::OK;
        }
    ); // REG_SET_SERVO_LOWER_BOUND

    RegisterManager::add_command(
        REG_SET_SERVO_UPPER_BOUND,
        sizeof(double),
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            ActionManager::add(Action::run_once(
                [bytes] -> void
                {
                    double data = ByteConverter::bytes_to_double(bytes);
                    m_servo.set_upper_limit(data);
                    
                    // Send Acknowledge Bytes
                    Serial.transmit_bytes(bytes);
                }
            ));

            return StatusCode::OK;
        }
    ); // GET_SET_SERVO_UPPER_BOUND

    RegisterManager::add_request(
        REG_GET_TIME,
        sizeof(double),
        [](std::vector<uint8_t>& write_buffer) -> StatusCode
        {
            double data = System::get_seconds();

            auto bytes = ByteConverter::double_to_bytes(data);

            Serial.transmit_bytes(bytes);

            return StatusCode::OK;
        }
    ); // REG_GET_TIME

    RegisterManager::add_request(
        REG_GET_SERVO,
        sizeof(double),
        [](std::vector<uint8_t>& write_buffer) -> StatusCode
        {
            double data = m_servo.get_angle(); 

            auto bytes = ByteConverter::double_to_bytes(data);

            Serial.transmit_bytes(bytes);

            return StatusCode::OK;
        }
    ); // REG_GET_SERVO

    RegisterManager::add_request(
        REG_GET_MOTOR,
        sizeof(double),
        [](std::vector<uint8_t>& write_buffer) -> StatusCode
        {
            double data = m_motor.get_percent();

            auto bytes = ByteConverter::double_to_bytes(data);

            Serial.transmit_bytes(bytes);

            return StatusCode::OK;
        }
    ); // REG_GET_MOTOR
    
} // end of "add_registers()"