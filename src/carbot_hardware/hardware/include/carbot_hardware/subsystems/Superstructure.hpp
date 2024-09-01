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
#include "SystemManager.hpp"
#include <iterator>

namespace subsystem{

    class Superstructure : public Subsystem{

        private:
            std::vector<subsystem::Subsystem> subsystems;

            
            
        public:         
            subsystem::SystemManager system_manager;
            subsystem::Drive drive;
  
            Superstructure() : Subsystem(){
                subsystems.emplace_back(system_manager);
                subsystems.emplace_back(drive);
            }

            void initialize(ArduinoUtility::Config config) override{
                drive.initialize(config);
            }

            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend() override{
                std::vector<ArduinoUtility::ArduinoMessage> commands;

                for(subsystem::Subsystem subsystem : subsystems){
                    std::vector<ArduinoUtility::ArduinoMessage> currentCommandPacket = subsystem.getMessagesToSend();

                    commands.insert(commands.end(), currentCommandPacket.begin(), currentCommandPacket.end());
                }

                return commands;
            }

            std::vector<hardware_interface::StateInterface> getStateInterfaces() override{
                std::vector<hardware_interface::StateInterface> state_interfaces;

                for(int j = 0; j < subsystems.size(), j++){
                    std::vector<hardware_interface::StateInterface> currentStateInterface = subsystems.at(j).getStateInterfaces();

                    for(int i = 0; i < currentStateInterface.size(); i++){
                        state_interfaces.emplace_back(currentStateInterface.at(i));
                    }
                }

                return state_interfaces;
            }

            std::vector<hardware_interface::CommandInterface> getCommandInterfaces() override{
                std::vector<hardware_interface::CommandInterface> command_interfaces;

                // for(subsystem::Subsystem subsystem : subsystems){
                //     std::vector<hardware_interface::CommandInterface> currentCommandInterface = subsystem.getCommandInterfaces();
                    
                //     for(int i = 0; i < currentCommandInterface.size(); i++){
                //         command_interfaces.emplace_back(currentCommandInterface.at(i));
                //     }
                // }

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