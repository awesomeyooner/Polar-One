#ifndef SUBSYSTEM_SUBSYSTEM_HPP
#define SUBSYSTEM_SUBSYSTEM_HPP

#include "carbot_hardware/arduino_interface_types.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include <vector>

#define BLANK_MESSAGE ArduinoUtility::ArduinoMessage{}

namespace subsystem{

    class Subsystem{

        private:

        public:

            Subsystem(){}

            virtual std::vector<ArduinoUtility::ArduinoMessage> getCommands(){return {BLANK_MESSAGE};}
            virtual std::vector<ArduinoUtility::ArduinoMessage> getStates(){return {BLANK_MESSAGE};}

            virtual std::vector<hardware_interface::StateInterface> getStateInterfaces() = 0;
            virtual std::vector<hardware_interface::CommandInterface> getCommandInterfaces() = 0;
            
            virtual void applyToAll(ArduinoUtility::ArduinoMessage message){}

    };
}

#endif