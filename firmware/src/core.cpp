#include "core.hpp"

#include "EmbeddedLib/System.hpp"
#include "EmbeddedLib/devices/led.hpp"
#include "EmbeddedLib/util/math/math_util.hpp"

#include "WireLib/communication/wire_manager.hpp"
#include "WireLib/communication/protocols/serial_interface.hpp"
#include "WireLib/util/byte_converter.hpp"

#include "ActionLib/ActionManager.hpp"

#include "devices/l298n.hpp"
#include "devices/servo.hpp"

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
using namespace math;
using namespace std;


LED led = LED(GPIOC, GPIO_PIN_1);

L298N motor = L298N(&htim8, TIM_CHANNEL_1, TIM_CHANNEL_2);
Servo servo = Servo(&htim3, TIM_CHANNEL_3);

void core_init()
{
    ActionManager::init();

    Serial.set_parse_type(ParseType::PACKET);

    WireManager::attach(Serial);

    RegisterManager::add_request(
        99,
        8,
        [](std::vector<uint8_t>& write_buffer) -> StatusCode
        {
            auto bytes = ByteConverter::double_to_bytes(System::get_seconds());

            Serial.transmit_bytes(bytes);

            return StatusCode::OK;
        }
    );

    RegisterManager::add_command(
        100,
        8,
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            double data = ByteConverter::bytes_to_double(bytes);
            servo.set_angle(data);

            return StatusCode::OK;
        }
    );

    RegisterManager::add_command(
        101,
        8,
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            
            double data = ByteConverter::bytes_to_double(bytes);
            motor.set_percent(data);

            return StatusCode::OK;
        }
    );

    RegisterManager::add_command(
        102,
        8,
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            ActionManager::add(Action::run_once(
                [bytes] -> void
                {
                    double data = ByteConverter::bytes_to_double(bytes);
                    servo.set_lower_limit(data);
                    
                    // Send Acknowledge Bytes
                    Serial.transmit_bytes(bytes);
                }
            ));

            return StatusCode::OK;
        }
    );

    RegisterManager::add_command(
        103,
        8,
        [](const std::vector<uint8_t>& bytes) -> StatusCode
        {
            ActionManager::add(Action::run_once(
                [bytes] -> void
                {
                    double data = ByteConverter::bytes_to_double(bytes);
                    servo.set_upper_limit(data);
                    
                    // Send Acknowledge Bytes
                    Serial.transmit_bytes(bytes);
                }
            ));

            return StatusCode::OK;
        }
    );

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
    servo.init();

    servo.set_ranges(0.035, 0.135, degrees_to_radians(270));
    servo.set_lower_limit(degrees_to_radians(120));
    servo.set_upper_limit(degrees_to_radians(150));
}

void core_update()
{
    ActionManager::update();
}


