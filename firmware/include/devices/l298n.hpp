#ifndef L298N_HPP
#define L298N_HPP

#include <cmath>

#include "tim.h"

#include "EmbeddedLib/util/status.hpp"
#include "devices/timer_device.hpp"


class L298N
{

    public:

        L298N(TIM_HandleTypeDef* timer, int in1, int in2);

        status_utils::StatusCode init();

        void set_percent(double percent);

    private:

        TimerDevice m_in1;
        TimerDevice m_in2;

}; // class L298N 


#endif // L298N_HPP