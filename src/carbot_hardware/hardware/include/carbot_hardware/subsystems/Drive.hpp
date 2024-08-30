#ifndef DRIVE_DRIVE_HPP
#define DRIVE_DRIVE_HPP

#include "carbot_hardware/arduino_interface_types.hpp"
#include <vector>
#include "Subsystem.hpp"
#include "carbot_hardware/devices/Motor.hpp"
#include "carbot_hardware/devices/Sensor.hpp"
#include "carbot_hardware/constants.hpp"
#include "carbot_hardware/hardware/include/carbot_hardware/diffbot_system.hpp"
#include "carbot_hardware/hardware/include/carbot_hardware/constants.hpp"
#include "hardware_interface/handle.hpp"

namespace subsystem{

    class Drive : public Subsystem{

        private:

        public:
            hardware_component::Motor drive_motor;
            hardware_component::Motor steer_motor;
            

            Drive(carbot_hardware::Config config) : Subsystem(){
                drive_motor.device = config.drive_id;
                steer_motor.device = config.steer_id;

                drive_motor.control_mode = MotorConstants::COMMAND_INTERFACE;
                steer_motor.control_mode = ServoConstants::COMMAND_INTERFACE;
            }

            std::vector<ArduinoUtility::ArduinoMessage> getCommands(){
            }

            std::vector<ArduinoUtility::ArduinoMessage> getStates(){

            }

            std::vector<hardware_interface::StateInterface> getStateInterfaces(){
                std::vector<hardware_interface::StateInterface> state_interfaces;

                state_interfaces.emplace_back(
                    drive_motor.device,
                    hardware_interface::HW_IF_VELOCITY,
                    &drive_motor.velocity
                );
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message){

            }

            void config_devices(){
                
            }

    };
}

#endif