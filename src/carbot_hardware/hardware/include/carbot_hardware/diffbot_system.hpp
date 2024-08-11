// Copyright 2021 ros2_control Development Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CARBOT_HARDWARE__DIFFBOT_SYSTEM_HPP_
#define CARBOT_HARDWARE__DIFFBOT_SYSTEM_HPP_

#include <memory>
#include <string>
#include <vector>

#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/clock.hpp"
#include "rclcpp/duration.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/time.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "rclcpp_lifecycle/state.hpp"

#include "carbot_hardware/visibility_control.h"

#include "arduino_comms.hpp"
#include "arduino_interface_types.hpp"

namespace carbot_hardware{

  class CarlikeBotSystemHardware : public hardware_interface::SystemInterface{

    struct Config{
      std::string port = "";

      std::string drive_id = "";
      std::string steer_id = "";

      std::string voltage_sensor_id = "";

      int32_t baud_rate = 0;
      int32_t loop_rate = 0;
      int32_t timeout_ms = 0;
    };

     struct Sensor{
      std::string device = "";
      std::string type_value = "";
      
      double value = 0;

      void apply(ArduinoComms::ArduinoMessage message){
            if(message.device != device)
                return;

            type_value = message.type_value;
            value = message.value;
        }
    };

    struct Motor{
      std::string device = "";
      std::string control_mode = ""; //if message_type is control
      double control_value = 0; //when message_type is control,  then command_value = value of packet

      double position = 0;
      double velocity = 0;
      double effort = 0;

      void apply(ArduinoComms::ArduinoMessage message){
            
            if(message.device != device)
                return;

            if(message.message_type == MessageType::STATUS && message.type_value == TypeValue::POSITION)
                position = message.value;
            
            else if(message.message_type == MessageType::STATUS && message.type_value == TypeValue::VELOCITY)
                velocity = message.value;
            
            else if(message.message_type == MessageType::STATUS && message.type_value == TypeValue::EFFORT)
                effort = message.value;
                
            if(message.message_type == MessageType::CONTROL){
                control_mode = message.type_value; //velocity or position or percent
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

    private:
      // Parameters for the DiffBot simulation
      double hw_start_sec_;
      double hw_stop_sec_;

      // Store the command for the simulated robot
      std::vector<double> hw_commands_;
      std::vector<double> hw_positions_;
      std::vector<double> hw_velocities_;

      ArduinoComms comms;
      Config config;

      Motor drive_motor;
      Motor steer_motor;

      Sensor voltage_sensor;

    public:
      RCLCPP_SHARED_PTR_DEFINITIONS(CarlikeBotSystemHardware);

      CARBOT_HARDWARE_PUBLIC
      hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

      CARBOT_HARDWARE_PUBLIC
      std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

      CARBOT_HARDWARE_PUBLIC
      std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

      CARBOT_HARDWARE_PUBLIC
      hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

      CARBOT_HARDWARE_PUBLIC
      hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

      CARBOT_HARDWARE_PUBLIC
      hardware_interface::return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;

      CARBOT_HARDWARE_PUBLIC
      hardware_interface::return_type write(const rclcpp::Time & time, const rclcpp::Duration & period) override;
  };

}  // namespace carbot_hardware

#endif  // CARBOT_HARDWARE__DIFFBOT_SYSTEM_HPP_
