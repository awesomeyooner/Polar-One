#ifndef SERVO_HPP
#define SERVO_HPP


#include "devices/timer_device.hpp"


class Servo : public TimerDevice
{

    public:

        Servo(TIM_HandleTypeDef* timer, int channel);

    private:

}; // class Servo

#endif // SERVO_HPP