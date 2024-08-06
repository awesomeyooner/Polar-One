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

#include "carbot_hardware/diffbot_system.hpp"

#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <vector>

#include "hardware_interface/lexical_casts.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "include/carbot_hardware/arduino_interface_types.hpp"
#include "rclcpp/rclcpp.hpp"
#include "include/carbot_hardware/constants.hpp"

namespace carbot_hardware{

hardware_interface::CallbackReturn CarlikeBotSystemHardware::on_init(const hardware_interface::HardwareInfo & info){

  if (hardware_interface::SystemInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS){
    return hardware_interface::CallbackReturn::ERROR;
  }

  config.port = info_.hardware_parameters["port"];

  config.drive_id = info_.hardware_parameters["drive_id"];
  config.steer_id = info_.hardware_parameters["steer_id"];

  config.voltage_sensor_id = info_.hardware_parameters["voltage_sensor_id"];

  config.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
  config.loop_rate = std::stoi(info_.hardware_parameters["loop_rate"]);
  config.timeout_ms = std::stoi(info_.hardware_parameters["timeout_ms"]);

  drive_motor.device = config.drive_id;
  drive_motor.control_mode = TypeValue::PERCENT;

  steer_motor.device = config.steer_id;
  steer_motor.control_mode = TypeValue::PERCENT;

  voltage_sensor.device = config.voltage_sensor_id;

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> CarlikeBotSystemHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  
  //======drive motor=======
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    drive_motor.device, 
    hardware_interface::HW_IF_VELOCITY, 
    &drive_motor.velocity
    ));

  state_interfaces.emplace_back(hardware_interface::StateInterface(
    drive_motor.device, 
    hardware_interface::HW_IF_POSITION, 
    &drive_motor.position
    ));

  //======steer motor=========
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    steer_motor.device, 
    hardware_interface::HW_IF_POSITION, 
    &steer_motor.position
    ));

  //=====voltage sensor=====
  state_interfaces.emplace_back(hardware_interface::StateInterface(
    voltage_sensor.device,
    TypeValue::VOLTAGE,
    &voltage_sensor.value
  ));


  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> CarlikeBotSystemHardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;
 
  //====drive motor=====
  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    drive_motor.device,
    hardware_interface::HW_IF_EFFORT,
    &drive_motor.control_value
  ));

  //====steer motor=====
  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    steer_motor.device,
    hardware_interface::HW_IF_EFFORT,
    &steer_motor.control_value
  ));

  return command_interfaces;
}


hardware_interface::CallbackReturn CarlikeBotSystemHardware::on_activate(const rclcpp_lifecycle::State & /*previous_state*/){
  RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), "Activating ...please wait...");
  comms.connect(config.port, config.baud_rate, config.timeout_ms);

  std::vector<ArduinoComms::ArduinoMessage> messages;

  messages.push_back(drive_motor.config_bound(TypeValue::LOWER_BOUND, MotorConstants::MAX_REVERSE));
  messages.push_back(drive_motor.config_bound(TypeValue::UPPER_BOUND, MotorConstants::MAX_FORWARD));
  messages.push_back(drive_motor.config_bound(TypeValue::NEUTRAL, MotorConstants::NEUTRAL));

  messages.push_back(steer_motor.config_bound(TypeValue::LOWER_BOUND, ServoConstants::MAX_RIGHT));
  messages.push_back(steer_motor.config_bound(TypeValue::UPPER_BOUND, ServoConstants::MAX_LEFT));

  comms.send_message(messages); 
  
  RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), "Successfully activated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn CarlikeBotSystemHardware::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/){
  RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), "Deactivating ...please wait...");
  comms.disconnect();
  RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), "Successfully deactivated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type CarlikeBotSystemHardware::read(const rclcpp::Time & /*time*/, const rclcpp::Duration & period){

  //RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), comms.debug().c_str());
  std::vector<ArduinoComms::ArduinoMessage> messages = comms.get_message_dump();
 
  for(ArduinoComms::ArduinoMessage message : messages){
    drive_motor.apply(message);
    steer_motor.apply(message);

    voltage_sensor.apply(message);
  }

  return hardware_interface::return_type::OK;
}

hardware_interface::return_type carbot_hardware ::CarlikeBotSystemHardware::write(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/){
  std::vector<ArduinoComms::ArduinoMessage> messages;

  messages.push_back(drive_motor.send_command(drive_motor.control_mode, drive_motor.control_value));
  messages.push_back(steer_motor.send_command(steer_motor.control_mode, steer_motor.control_value));

  //RCLCPP_INFO(rclcpp::get_logger("CarlikeBotSystemHardware"), comms.debug(messages).c_str());

  comms.send_message(messages); 

  return hardware_interface::return_type::OK;
}

}  // namespace carbot_hardware

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  carbot_hardware::CarlikeBotSystemHardware, hardware_interface::SystemInterface)
