#ifndef SENSOR_SENSOR_HPP
#define SENSOR_SENSOR_HPP

#include <nlohmann/json.hpp>

#include "Device.hpp"

using json = nlohmann::json;


class Sensor : public Device{

    private:

    public:

        std::string device;
        std::string type_value;
        double value;

        void apply(ArduinoComms::ArduinoMessage message) override{
            if(message.device != device)
                return;

            type_value = message.type_value;
            value = message.value;
        }
};

#endif