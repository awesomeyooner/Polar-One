#ifndef SERVO_HPP
#define SERVO_HPP


#include <cmath>

#include "devices/timer_device.hpp"


class Servo : public TimerDevice
{

    public:

        Servo(TIM_HandleTypeDef* timer, int channel);

        /**
         * @brief Sets the duty cycle and angle range of this servo
         * 
         * @param min_duty `double` The minimum duty cycle `[0, 1]` to set the min angle
         * @param max_duty `double` The maximum duty cycle `[0, 1]` to set the max angle
         * @param angle_range `double` max angle - min angle, the range of the servo in radians
         */
        void set_ranges(double min_duty, double max_duty, double angle_range);

        /**
         * @brief Sets the lower limit this servo can move to in radians. This is not based on the motor itself,
         * but how far you want it to move
         * 
         * @param limit `double` The limit in radians
         */
        void set_lower_limit(double limit);

        /**
         * @brief Sets the upper limit this servo can move to in radians. This is not based on the motor itself,
         * but how far you want it to move
         * 
         * @param limit `double` The limit in radians
         */
        void set_upper_limit(double limit);

        /**
         * @brief Sets the angle of the servo in radians
         * 
         * @param radians `double`
         */
        void set_angle(double radians);

        /**
         * @brief Gets the theoretical angle of the servo in radians
         * 
         * @return `double` The angle in radians 
         */
        double get_angle();

        /**
         * @brief Stops the servo (sets the duty cycle to 0)
         * 
         */
        void stop();

    private:

        // The min duty cycle that represents the lower bound of the servo
        double m_min_duty = -1;

        // The max duty cycle that represents the upper bound of the servo
        double m_max_duty = -1;

        // The range of the angle in radians. Ex: 270 degrees (to radians) means the servo can only move 270 degrees
        double m_angle_range = -1;

        // The user-defined lower angle limit that this servo is limited to
        double m_lower_angle_limit = -1;

        // The user-defined upper angle limit that this servo is limited to
        double m_upper_angle_limit = -1;

        /**
         * @brief Gets the conversion from radians to duty cycle
         * 
         * @return `double` Duty Cycle to radians
         */
        double get_duty_per_radian();

        /**
         * @brief Clamps the angle between the lower and upper limits. 
         * If they are not set (`= -1`), the limit will not be applied
         * 
         * @param radians `double` The input angle in radians
         * @return `double` 
         */
        double get_clamped_angle(double radians);

}; // class Servo

#endif // SERVO_HPP