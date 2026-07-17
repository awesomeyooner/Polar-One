#include "core.hpp"

#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/devices/led.hpp"
#include "EmbeddedLib/math/math_util.hpp"

#include "WireLib/communication/wire_manager.hpp"
#include "WireLib/communication/protocols/serial_interface.hpp"
#include "WireLib/util/byte_converter.hpp"

#include "ActionLib/ActionManager.hpp"

#include "devices/l298n.hpp"
#include "devices/servo.hpp"

#include "hardware_manager.hpp"

#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include <stdio.h>
#include <functional>


using namespace status_utils;
using namespace math;
using namespace std;


LED led = LED(GPIOC, GPIO_PIN_1);

void core_init()
{
    ActionManager::init();

    Serial.set_parse_type(ParseType::PACKET);

    WireManager::attach(Serial);

    HardwareManager::init();
    HardwareManager::add_registers();

    Action blink_led = Action(0.5);

    blink_led.link_callback(
        [](double timestamp, double time_since_last) -> StatusedValue<bool>
        {
            if(System::is_OK())
                led.toggle();
            else
                led.on();

            return StatusedValue<bool>(false, StatusCode::OK);
        }
    );

    ActionManager::add(blink_led);

} // end of "core_init()"

void core_update()
{
    System::update();
    ActionManager::update();
    HardwareManager::update();

} // end of "core_update()"


