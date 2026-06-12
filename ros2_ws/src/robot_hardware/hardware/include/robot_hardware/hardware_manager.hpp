#ifndef HARDWARE_MANAGER_HPP
#define HARDWARE_MANAGER_HPP


#include <memory>
#include <string>
#include <vector>

#include "CommiFaceLib/protocols/serial.hpp"

#include "plib/math/units.hpp"


class HardwareManager
{

    public:

        /**
         * @brief Get the underlying SerialInterface object
         * 
         * @return `SerialInterface&` 
         */
        SerialInterface& get_serial_port();

        /**
         * @brief Initialize the serial port using the given field and matching description
         * 
         * @param field_name `std::string` The field name. ie: `product`
         * @param description `std::string` The description for the field. ie: `STM32 Virtual ComPort`
         * @return `status_utils::StatusCode` OK if device was found, FAILED otherwise 
         */
        status_utils::StatusCode init(std::string field_name, std::string description);

        /**
         * @brief Closes the serial port
         * 
         */
        void close();

        /**
         * @brief Set the servo angle in radians
         * 
         * @param radians `double`
         * @return `status_utils::StatusCode` OK if sent successfully, FAILED otherwise 
         */
        status_utils::StatusCode set_servo(double radians);

        /**
         * @brief Set the servo angle from the center in radians
         * 
         * @param radians `double`
         * @return `status_utils::StatusCode` OK if sent successfully, FAILED otherwise 
         */
        status_utils::StatusCode set_servo_from_center(double radians);

        /**
         * @brief Set the servo angle a percentage from the center. The percentage is determined by the bounds.
         * 
         * Example: If the center is 90 degrees and the lower and upper bounds are 45 and 135 respectively, then 100% (1) will be 135 and
         * -100% (-1) will be 45. Anything is between is just the lerp.
         * 
         * @param percent_from_center 
         * @return status_utils::StatusCode 
         */
        status_utils::StatusCode set_servo_percent_from_center(double percent);

        /**
         * @brief Set the percent output of the motor from [-1, 1]
         * 
         * @param percent `double`
         * @return `status_utils::StatusCode` OK if sent successfully, FAILED otherwise 
         */
        status_utils::StatusCode set_motor(double percent);

        /**
         * @brief Set the lower and upper bounds of the servo in radians
         * 
         * @param lower_radians `double` Radians
         * @param upper_radians `double` Radians
         * @return `status_utils::StatusCode` OK if sent successfully, FAILED otherwise 
         */
        status_utils::StatusCode set_servo_bounds(double lower_radians, double upper_radians);

        /**
         * @brief Set the center of the servo's position in radians
         * 
         * @param center_radians `double` Radians
         */
        void set_servo_center(double center_radians);

    private:

        // REGISTERS
        const uint8_t REG_SERVO_POSITION = 100;
        const uint8_t REG_MOTOR_PERCENT = 101;

        const uint8_t REG_SERVO_LOWER_LIMIT = 102;
        const uint8_t REG_SERVO_UPPER_LIMIT = 103;

        double m_servo_lower_bound = -1;
        double m_servo_upper_bound = -1;
        double m_servo_center = -1;

        // Underlying serial connection
        SerialInterface m_serial_port;

}; // class HardwareManager


#endif // HARDWARE_MANAGER_HPP