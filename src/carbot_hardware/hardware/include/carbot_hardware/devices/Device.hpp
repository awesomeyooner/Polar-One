#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "carbot_hardware/arduino_comms.hpp"
#include "carbot_hardware/arduino_interface_types.hpp"
#include <string>

namespace hardware_component{

    struct InterfaceValue{
        std::string interface_type;
        double value;

        InterfaceValue(std::string if_type, double val) : interface_type(if_type), value(val){}
        InterfaceValue(std::string if_type) : interface_type(if_type), value(0.0){}
        InterfaceValue() : interface_type(""), value(0.0){}
    };

    class Device{

        private:

        public:

            Device(){}
            
            virtual std::vector<hardware_interface::StateInterface> getStateInterfaces(){return {};};
            virtual std::vector<hardware_interface::CommandInterface> getCommandInterfaces(){return {};}

            virtual ArduinoUtility::ArduinoMessage send_message(std::string message_type, std::string type_value, double value){
                return ArduinoUtility::ArduinoMessage{
                    .device = device,
                    .message_type = message_type,
                    .type_value = type_value,
                    .value = value
                };
            }

            virtual ArduinoUtility::ArduinoMessage send_message(){return {};}

            virtual void apply(ArduinoUtility::ArduinoMessage message){}

            std::string device;
            


    };
}

#endif