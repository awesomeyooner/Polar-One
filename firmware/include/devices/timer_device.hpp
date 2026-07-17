#ifndef TIMER_DEVICE_HPP
#define TIMER_DEVICE_HPP


#include "EmbeddedLib/status.hpp"

#include "tim.h"


class TimerDevice
{

    public:

        /**
         * @brief Creates a new TimerDevice that represents the given channel on the given timer
         * 
         * @param timer `TIM_HandleTypeDef*` The timer to use, like `&htim1` for instance
         * @param channel `int` The channel to use, like `TIM_CHANNEL_1` for instance
         */
        TimerDevice(TIM_HandleTypeDef* timer, int channel);

        /**
         * @brief Starts the timer and PWM
         * 
         * @return `status_utils::StatusCode` OK if timer and PWM return HAL_OK, FAILED otherwise 
         */
        status_utils::StatusCode init();

        /**
         * @brief Sets the duty cycle of the channel, from `[0, 1]`. 
         * 
         * Example: `0.5` is 50% duty cycle.
         * 
         * This will clamp input to [0, 1]
         * 
         * @param duty `double` The duty cycle from `[0, 1]`
         */
        void set_duty(double duty);

        /**
         * @brief Sets the prescalar of the timer.
         * This is the same as `htimx.Init.Prescaler`
         * This function automatically applys the new value, so no need to restart
         * 
         * @param psc `int`
         */
        void set_PSC(int psc);

        /**
         * @brief Sets the Auto Reload Register of the timer.
         * This is the same as `htimx.Init.Period`
         * 
         * @param arr `int`
         */
        void set_ARR(int arr);

        /**
         * @brief Get the underlying timer handle
         * 
         * @return `TIM_HandleTypeDef*` 
         */
        TIM_HandleTypeDef* get_timer();

        /**
         * @brief Get the channel this object represents
         * 
         * @return `int` 
         */
        int get_channel();

        /**
         * @brief Get the timer clock frequency in Hz. 
         * This is the same as `APBx timer clocks` in CubeMX
         * 
         * @return `int` Frequency in Hz 
         */
        int get_clock_freq();

        /**
         * @brief Get the PWM frequency in Hz of the timer with the ARR and PSC
         * 
         * @return `double` Frequency in Hz. This is double because ARR and PSC might not
         * divide cleanly into the clock frequency
         */
        double get_PWM_freq();

        /**
         * @brief Gets the duty cycle currently applied from `[0, 1]`
         * 
         * @return `double` Duty cycle from `[0, 1]`
         */
        double get_duty();

    protected:

        // Underlying timer handle
        TIM_HandleTypeDef* m_timer = nullptr;

        // Timer Channel
        int m_channel = -1;

    private:

        /**
         * @brief Gets if the timer used is an advanced timer.
         * For F4 series, that is timers 1 and 8
         * 
         * 
         * @return `true` If timer is 1 or 8
         * @return `false` If not 1 nor 8 
         */
        bool is_advanced_timer();

        /**
         * @brief Gets if the timer is on the APB2 bus.
         * 
         * @return `true` 
         * @return `false` 
         */
        bool is_APB2();

        /**
         * @brief Gets if the timer is on the APB1 bus.
         * 
         * @return `true` 
         * @return `false` 
         */
        bool is_APB1();

        /**
         * @brief Gets the APB prescalar value. Will return APB1 or APB2
         * depending on the timer used
         * 
         * @return `int` The prescalar. `1, 2, 4, 8, 16`
         */
        int get_APB_prescaler();

}; // class TimerDevice


#endif // TIMER_DEVICE_HPP