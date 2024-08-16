#ifndef MOTOR_MOTOR_HPP
#define MOTOR_MOTOR_HPP

#include "Device.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace hardware_component{

    class Motor : public Device{

        public:
            std::string control_mode;
            double control_value; 

            double position = 0;
            double velocity = 0;
            double effort = 0;

            Motor() = default;
            
            void apply(ArduinoComms::ArduinoMessage message){
                if(message.device != device)
                    return;

                if(message.message_type == MessageType::STATUS){
                    if(message.type_value == TypeValue::POSITION)
                        position = message.value;
                    else if(message.type_value == TypeValue::VELOCITY)
                        velocity = message.value;
                    else if(message.type_value == TypeValue::EFFORT)
                        effort = message.value;
                }

                else if(message.message_type == MessageType::CONTROL){
                    control_mode = message.type_value;
                    control_value = message.value;
                }
            }

            ArduinoComms::ArduinoMessage send_command(std::string mode, double value){
                return ArduinoComms::ArduinoMessage{
                    .device = device,
                    .message_type = MessageType::CONTROL,
                    .type_value = mode,
                    .value = value
                };
            }

            ArduinoComms::ArduinoMessage config_bound(std::string type, double value){
                return ArduinoComms::ArduinoMessage{
                    .device = device,
                    .message_type = MessageType::CONFIG,
                    .type_value = type,
                    .value = value
                };
            }
    };
}
#endif