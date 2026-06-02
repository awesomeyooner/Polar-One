#include "core.hpp"

#include "EmbeddedLib/System.hpp"
#include "EmbeddedLib/devices/led.hpp"

#include "WireLib/communication/wire_manager.hpp"
#include "WireLib/communication/protocols/serial_interface.hpp"
#include "WireLib/util/byte_converter.hpp"

#include "ActionLib/ActionManager.hpp"

#include "devices/l298n.hpp"

#include <functional>

#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include <stdio.h>


using namespace status_utils;
using namespace std;


LED led = LED(GPIOC, GPIO_PIN_1);

L298N motor = L298N(&htim8, TIM_CHANNEL_1, TIM_CHANNEL_2);

void core_init()
{
    ActionManager::init();

    Serial.set_parse_type(ParseType::PACKET);

    WireManager::attach(Serial);

    RegisterManager::add_command(
        100,
        8,
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            string data = ByteConverter::bytes_to_string(bytes);

            ActionManager::add(Action::run_once(
                [data] -> void
                {
                    Serial.print(data);
                }
            ));

            return StatusCode::OK;
        }
    );

    // Serial.configure_on_receive(
    //     [](const vector<uint8_t>& bytes) -> StatusCode
    //     {
    //         Action print_data = Action::run_once(
    //             [bytes]() -> void
    //             {
    //                 string text = ByteConverter::bytes_to_string(bytes);

    //                 Serial.info(text);
    //             }
    //         );

    //         ActionManager::add(print_data);

    //         return StatusCode::OK;
    //     }
    // );

    Action say_hello = Action(0.5);

    say_hello.link_callback(
        [](double timestamp, double time_since_last) -> StatusedValue<bool>
        {
            led.toggle();
            // Serial.info("Hello World!");

            return StatusedValue<bool>(false, StatusCode::OK);
        }
    );

    ActionManager::add(say_hello);

    motor.init();
}

void core_update()
{
    ActionManager::update();

    // motor.set_percent(0.5);
}


