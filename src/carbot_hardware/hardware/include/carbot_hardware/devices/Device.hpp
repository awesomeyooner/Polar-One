#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "carbot_hardware/arduino_comms.hpp"
#include "carbot_hardware/arduino_interface_types.hpp"

namespace hardware_component{

    class Device{

        private:

        public:

            Device() = default;

            virtual ArduinoComms::ArduinoMessage send_message(std::string message_type, std::string type_value, double value){
                return ArduinoComms::ArduinoMessage{
                    .device = device,
                    .message_type = message_type,
                    .type_value = type_value,
                    .value = value
                };
            }

            virtual void apply(ArduinoComms::ArduinoMessage message){}

            std::string device;
            double value;


    };
}

#endif