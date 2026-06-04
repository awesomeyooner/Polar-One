#include "devices/servo.hpp"


Servo::Servo(TIM_HandleTypeDef* timer, int channel)
    : TimerDevice(timer, channel)
{} // end of "Servo(TIM_HandleTypeDef*, int)"