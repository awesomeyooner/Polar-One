#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "carbot_hardware/arduino_comms.hpp"
#include "carbot_hardware/arduino_interface_types.hpp"

namespace hardware_component{

    struct InterfaceValue{
        std::string interface_type = "";
        double value = 0;
    };

    class Device{

        private:

        public:

            Device() = default;

            virtual ArduinoUtility::ArduinoMessage send_message(std::string message_type, std::string type_value, double value){
                return ArduinoUtility::ArduinoMessage{
                    .device = device,
                    .message_type = message_type,
                    .type_value = type_value,
                    .value = value
                };
            }

            virtual void apply(ArduinoUtility::ArduinoMessage message){}

            std::string device;
            double value;


    };
}

#endif