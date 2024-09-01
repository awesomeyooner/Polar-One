#ifndef SUPERSTRUCTURE_SUPERSTRUCTURE_HPP
#define SUPERSTRUCTURE_SUPERSTRUCTURE_HPP

#include "carbot_hardware/arduino_interface_types.hpp"
#include <vector>
#include "Subsystem.hpp"
#include "carbot_hardware/devices/Motor.hpp"
#include "carbot_hardware/devices/Sensor.hpp"
#include "carbot_hardware/constants.hpp"
#include "carbot_hardware/diffbot_system.hpp"
#include "carbot_hardware/constants.hpp"
#include "hardware_interface/handle.hpp"
#include "Drive.hpp"

namespace subsystem{

    class Superstructure : public Subsystem{

        private:
            std::vector<subsystem::Subsystem> subsystems;

            subsystem::Drive drive;

        public:         
  
            Superstructure() : Subsystem(){
                subsystems.emplace_back(drive);
            }

            void initialize(ArduinoUtility::Config config) override{
                for(subsystem::Subsystem subsystem : subsystems){
                    subsystem.initialize(config);
                }
            }

            std::vector<ArduinoUtility::ArduinoMessage> getCommands() override{
                std::vector<ArduinoUtility::ArduinoMessage> commands;

                for(subsystem::Subsystem subsystem : subsystems){
                    std::vector<ArduinoUtility::ArduinoMessage> currentCommandPacket = subsystem.getCommands();

                    commands.insert(commands.end(), currentCommandPacket.begin(), currentCommandPacket.end());
                }

                return commands;
            }

            std::vector<hardware_interface::StateInterface> getStateInterfaces() override{
                std::vector<hardware_interface::StateInterface> state_interfaces;

                for(subsystem::Subsystem subsystem : subsystems){
                    std::vector<hardware_interface::StateInterface> currentStateInterface = subsystem.getStateInterfaces();

                    //state_interfaces.insert(state_interfaces.end(), currentStateInterface.begin(), currentStateInterface.end());
                }

                return state_interfaces;
            }

            std::vector<hardware_interface::CommandInterface> getCommandInterfaces() override{
                std::vector<hardware_interface::CommandInterface> command_interfaces;

                for(subsystem::Subsystem subsystem : subsystems){
                    std::vector<hardware_interface::CommandInterface> currentCommandInterface = subsystem.getCommandInterfaces();
                    
                    //command_interfaces.insert(command_interfaces.end(), currentCommandInterface.begin(), currentCommandInterface.end());

                    return subsystem.getCommandInterfaces();
                }

                return command_interfaces;
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message) override{
                for(subsystem::Subsystem subsystem : subsystems){
                    subsystem.applyToAll(message);
                }
            }

            std::vector<ArduinoUtility::ArduinoMessage> configDevices() override{
                std::vector<ArduinoUtility::ArduinoMessage> messages;

                for(subsystem::Subsystem subsystem : subsystems){
                    std::vector<ArduinoUtility::ArduinoMessage> currentConfigPacket = subsystem.configDevices();

                    messages.insert(messages.end(), currentConfigPacket.begin(), currentConfigPacket.end());
                }

                return messages;
            }

    };
}

#endif