#ifndef L298N_HPP
#define L298N_HPP

#include <cmath>

#include "tim.h"


class L298N
{

    public:

        L298N(TIM_HandleTypeDef* timer, int in1, int in2);

        void init();

        void set_percent(double percent);

    private:

        TIM_HandleTypeDef* m_timer = nullptr;

        int m_in1;
        int m_in2;


        void set_duty_cycle(int duty, int pin);

}; // class L298N 


#endif // L298N_HPP