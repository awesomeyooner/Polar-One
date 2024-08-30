#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <nlohmann/json.hpp>

#include "Device.hpp"
#include "carbot_hardware/arduino_interface_types.hpp"

using json = nlohmann::json;

namespace hardware_component{

    class Sensor : public Device{

        private:

        public:

            std::string type_value;
            double value;

            Sensor() = default;

            void apply(ArduinoUtility::ArduinoMessage message){
                if(message.device != device)
                    return;

                type_value = message.type_value;
                value = message.value;
            }

            ArduinoUtility::ArduinoMessage send_message(std::string type_value, double value){
                return ArduinoUtility::ArduinoMessage{
                    .device = device,
                    .message_type = MessageType::STATUS,
                    .type_value = type_value,
                    .value = value
                };
            }

            ArduinoUtility::ArduinoMessage send_message(){
                send_message(type_value, value);
            }
            
    };
}

#endif