#ifndef GPIO_DEVICE_HPP
#define GPIO_DEVICE_HPP


#include "EmbeddedLib/util/status.hpp"

#include "gpio.h"

#include <stm32f446xx.h>


class GPIODevice
{

    public:

        /**
         * @brief Creates a new GPIO pin wrapper with the given GPIO Family and pin number
         * 
         * Example:
         * 
         * `PA13` <-> `GPIODevice(GPIOA, GPIO_PIN_13)`
         * 
         * @param gpio_family 
         * @param pin 
         */
        GPIODevice(GPIO_TypeDef* gpio_family, uint16_t pin);

        /**
         * @brief Gets the PinState of this pin
         * 
         * `GPIO_PIN_SET` for `HIGH`
         * 
         * `GPIO_PIN_RESET` for `LOW`
         * 
         * @return `GPIO_PinState` 
         */
        GPIO_PinState get_state();

        /**
         * @brief Gets if the pin is set to high or not
         * 
         * @return `true` If the pin state is `GPIO_PIN_SET`
         * @return `false` If the pin state is `GPIO_PIN_RESET`
         */
        bool is_high();

        /**
         * @brief Set the pin `HIGH`
         * 
         */
        void set_high();

        /**
         * @brief Set the pin `LOW`
         * 
         */
        void set_low();

        /**
         * @brief Sets the pin depending on the boolean given. `True` sets the
         * pin `HIGH`, `False` sets the pin `LOW`
         * 
         * @param should_set_high `bool` Whether or not to set the pin high
         */
        void toggle(bool should_set_high);

        /**
         * @brief Toggles the pin so that if the pin is `HIGH`, it'll be set to `LOW`
         * and vice versa
         * 
         */
        void toggle();

    private:

        // The GPIO Family, i.e. PA13 is `GPIOA`
        GPIO_TypeDef* m_gpio_family = nullptr;

        // The GPIO pin number, i.e. PA13 is `GPIO_PIN_13`
        uint16_t m_pin = 0;

        /**
         * @brief HAL wrapper to set the pin
         * 
         * @param state `GPIO_PinState` `GPIO_PIN_SET` for `HIGH` or `GPIO_PIN_RESET` for `LOW`
         */
        void set(GPIO_PinState state);

}; // class GPIODevice


#endif // GPIO_DEVICE_HPP