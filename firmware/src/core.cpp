#include "core.hpp"

#include "EmbeddedLib/System.hpp"
#include "EmbeddedLib/devices/led.hpp"

#include "WireLib/communication/protocols/serial_interface.hpp"
#include "ActionLib/ActionManager.hpp"

#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include <stdio.h>


using namespace status_utils;


LED led = LED(GPIOC, GPIO_PIN_1);

void core_init()
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    ActionManager::init();

    Action say_hello = Action(0.5);

    say_hello.link_callback(
        [](double timestamp, double time_since_last) -> StatusedValue<bool>
        {
            Serial.info("Hello World!");

            return StatusedValue<bool>(false, StatusCode::OK);
        }
    );

    ActionManager::add(say_hello);
}

void core_update()
{
    ActionManager::update();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 45);

}