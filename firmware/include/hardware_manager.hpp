#ifndef HARDWARE_MANAGER_HPP
#define HARDWARE_MANAGER_HPP


#include "EmbeddedLib/system.hpp"
#include "EmbeddedLib/devices/led.hpp"
#include "EmbeddedLib/math/math_util.hpp"

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


class HardwareManager
{

    public:

        static void init();

        

        static void update();

        static void stop();

        static void add_registers();

    private:

        static const uint8_t REG_SET_SERVO = 100;
        static const uint8_t REG_SET_MOTOR = 101;
        static const uint8_t REG_SET_SERVO_LOWER_BOUND = 102;
        static const uint8_t REG_SET_SERVO_UPPER_BOUND = 103;

        static const uint8_t REG_GET_TIME = 99;
        static const uint8_t REG_GET_MOTOR = 104;
        static const uint8_t REG_GET_SERVO = 105;

        static inline L298N m_motor = L298N(&htim8, TIM_CHANNEL_1, TIM_CHANNEL_2);
        static inline Servo m_servo = Servo(&htim3, TIM_CHANNEL_3);
    

}; // class HardwareManager


#endif // HARDWARE_MANAGER_HPP