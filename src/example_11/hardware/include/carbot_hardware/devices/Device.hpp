#ifndef DEVICE_DEVICE_HPP
#define DEVICE_DEVICE_HPP

#include "carbot_hardware/arduino_comms.hpp"

class Device{

    private:

    public:

        std::vector<ArduinoComms::ArduinoMessage> internal_state;

        virtual std::vector<ArduinoComms::ArduinoMessage> get_state(){
            return internal_state;
        }

        virtual void update_state(std::vector<ArduinoComms::ArduinoMessage> new_state){
            internal_state = new_state;
        }

        virtual void apply(ArduinoComms::ArduinoMessage message);


};

#endif