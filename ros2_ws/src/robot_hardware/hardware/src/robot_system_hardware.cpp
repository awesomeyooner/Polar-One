#include "robot_hardware/robot_system_hardware.hpp"

#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <vector>

#include "hardware_interface/lexical_casts.hpp"
#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"


using namespace robot_hardware;
using namespace hardware_interface;
using namespace std;


CallbackReturn RobotSystemHardware::on_init(const HardwareComponentInterfaceParams& params){

  if (SystemInterface::on_init(params) != CallbackReturn::SUCCESS)
    return CallbackReturn::ERROR;

  return CallbackReturn::SUCCESS;
}

vector<StateInterface> RobotSystemHardware::export_state_interfaces(){
  return {};
}

vector<CommandInterface> RobotSystemHardware::export_command_interfaces(){
  return {};
}

CallbackReturn RobotSystemHardware::on_activate(const rclcpp_lifecycle::State & /*previous_state*/){
  RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Activating ...please wait...");
  
  
  RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Successfully activated!");

  return CallbackReturn::SUCCESS;
}

CallbackReturn RobotSystemHardware::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/){
  RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Deactivating ...please wait...");

  RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Successfully deactivated!");

  return CallbackReturn::SUCCESS;
}

return_type RobotSystemHardware::read(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{

  return return_type::OK;
}

return_type RobotSystemHardware::write(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{

  return return_type::OK;
}


#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  robot_hardware::RobotSystemHardware, SystemInterface)
