#ifndef MOTOR_MOTOR_HPP
#define MOTOR_MOTOR_HPP

#include "Device.hpp"
#include "nlohmann/json.hpp"
#include "ros2_control_demo_example_2/arduino_interface_types.hpp"

using json = nlohmann::json;

class Motor : public Device{

    public:
        std::string device;
        std::string control_mode; //if message_type is control
        double control_value; //when message_type is control,  then command_value = value of packet

        double position;
        double velocity;
        
        void apply(ArduinoComms::ArduinoMessage message) override{
            
            if(message.device != device)
                return;

            if(message.message_type == ArduinoValue::STATUS && message.type_value == ArduinoValue::POSITION)
                position = message.value;
            
            else if(message.message_type == ArduinoValue::STATUS && message.type_value == ArduinoValue::VELOCITY)
                velocity = message.value;

            if(message.message_type == ArduinoValue::CONTROL){
                control_mode = message.type_value; //velocity or position or percent
                control_value = message.value;
            }
        }

        ArduinoComms::ArduinoMessage send_command(std::string mode, double value){
            return ArduinoComms::ArduinoMessage{
                .device = device,
                .message_type = ArduinoValue::CONTROL,
                .type_value = mode,
                .value = value
            };
        }

        
};

#endif