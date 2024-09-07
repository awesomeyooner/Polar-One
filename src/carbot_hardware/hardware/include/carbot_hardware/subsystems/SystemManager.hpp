#ifndef SYSTEM_MANAGER_SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_SYSTEM_MANAGER_HPP

#include "carbot_hardware/arduino_interface_types.hpp"
#include <vector>
#include "Subsystem.hpp"
#include "carbot_hardware/devices/Motor.hpp"
#include "carbot_hardware/devices/Sensor.hpp"
#include "carbot_hardware/constants.hpp"
#include "carbot_hardware/diffbot_system.hpp"
#include "carbot_hardware/constants.hpp"
#include "hardware_interface/handle.hpp"
#include "rclcpp/rclcpp.hpp"

namespace subsystem{

    class SystemManager : public Subsystem{

        private:
            hardware_component::Sensor heartbeat_sensor;
            hardware_component::Sensor voltage_sensor;

            std::vector<hardware_component::Device*> devices;

        public:         
  
            SystemManager() : Subsystem(),
             heartbeat_sensor(TypeValue::RAW), 
             voltage_sensor(TypeValue::VOLTAGE){

                devices.emplace_back(&heartbeat_sensor);
                devices.emplace_back(&voltage_sensor);
            }

            void initialize(ArduinoUtility::Config config) override{
                heartbeat_sensor.device = config.heartbeat_id;
                voltage_sensor.device = config.voltage_sensor_id;
            }

            std::vector<ArduinoUtility::ArduinoMessage> getMessagesToSend() override{
                std::vector<ArduinoUtility::ArduinoMessage> messages;

                for(hardware_component::Device* device : devices){
                    messages.emplace_back(device->send_message());
                }

                return messages;
            }

            std::vector<hardware_interface::StateInterface> getStateInterfaces() override{
                std::vector<hardware_interface::StateInterface> state_interfaces;

                state_interfaces.emplace_back(heartbeat_sensor.getStateInterface(&heartbeat_sensor.state));
                state_interfaces.emplace_back(voltage_sensor.getStateInterface(&voltage_sensor.state));

                return state_interfaces;
            }

            void applyToAll(ArduinoUtility::ArduinoMessage message) override{
                //double first = heartbeat_sensor.state.value;

                for(hardware_component::Device* device : devices){
                    device->apply(message);
                }

                //RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), std::to_string(heartbeat_sensor.state.value - first).c_str());
            }
    };
}

#endif