#ifndef SUBSYSTEM_SUBSYSTEM_HPP
#define SUBSYSTEM_SUBSYSTEM_HPP

#include "carbot_hardware/arduino_interface_types.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include <vector>
#include "carbot_hardware/diffbot_system.hpp"

namespace subsystem{

    class Subsystem{

        private:

        public:

            Subsystem(){}

            virtual std::vector<ArduinoUtility::ArduinoMessage> getCommands(){return {};}
        
            virtual std::vector<hardware_interface::StateInterface> getStateInterfaces(){return {};};
            virtual std::vector<hardware_interface::CommandInterface> getCommandInterfaces(){return {};}

            virtual std::vector<ArduinoUtility::ArduinoMessage> configDevices(){return {};}

            virtual void initialize(ArduinoUtility::Config config){}

            virtual void applyToAll(ArduinoUtility::ArduinoMessage message){}

    };
}

#endif