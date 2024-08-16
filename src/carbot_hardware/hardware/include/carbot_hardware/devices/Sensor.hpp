#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <nlohmann/json.hpp>

#include "Device.hpp"

using json = nlohmann::json;

namespace hardware_component{

    class Sensor : public Device{

        private:

        public:

            std::string message_type;
            std::string type_value;
            double value;

            Sensor() = default;

            void apply(ArduinoComms::ArduinoMessage message){
                if(message.device != device)
                    return;

                type_value = message.type_value;
                value = message.value;
            }

            virtual ArduinoComms::ArduinoMessage send_message(std::string message_type, std::string type_value, double value){
                return ArduinoComms::ArduinoMessage{
                    .device = device,
                    .message_type = message_type,
                    .type_value = type_value,
                    .value = value
                };
            }
            
    };
}

#endif