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
using namespace status_utils;
using namespace units;
using namespace std;


CallbackReturn RobotSystemHardware::on_init(const HardwareComponentInterfaceParams& params)
{

    if (SystemInterface::on_init(params) != CallbackReturn::SUCCESS)
        return CallbackReturn::ERROR;

    // 1. Initialize the serial port

        // Initialize the serial port with the given field and description
        // i.e. the "product" field should be "STM32 Virtual ComPort"
        string field_name = info_.hardware_parameters["MCU_field"];
        string description = info_.hardware_parameters["MCU_description"];

        StatusCode serial_init_status = m_hardware.init(field_name, description);

    if(serial_init_status != StatusCode::OK)
        return CallbackReturn::ERROR;

    return CallbackReturn::SUCCESS;

} // end of "on_init(const HardwareComponentInterfaceParams&)"


vector<StateInterface> RobotSystemHardware::export_state_interfaces()
{
    vector<StateInterface> state_interfaces;

    // There are none for now

    return state_interfaces;

} // end of "export_state_interfaces()"


vector<CommandInterface> RobotSystemHardware::export_command_interfaces()
{
    vector<CommandInterface> command_interfaces;

    command_interfaces.emplace_back(CommandInterface("front_left_wheel_joint", HW_IF_VELOCITY, &drive_commands[0]));
    command_interfaces.emplace_back(CommandInterface("front_right_wheel_joint", HW_IF_VELOCITY, &drive_commands[1]));
    command_interfaces.emplace_back(CommandInterface("rear_left_wheel_joint", HW_IF_VELOCITY, &drive_commands[2]));
    command_interfaces.emplace_back(CommandInterface("rear_right_wheel_joint", HW_IF_VELOCITY, &drive_commands[3]));

    command_interfaces.emplace_back(CommandInterface("front_left_steer_joint", HW_IF_POSITION, &steer_commands[0]));
    command_interfaces.emplace_back(CommandInterface("front_right_steer_joint", HW_IF_POSITION, &steer_commands[1]));

    return command_interfaces;

} // end of "export_command_interfaces()"


CallbackReturn RobotSystemHardware::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
    RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Activating ...please wait...");
    
    // Nothing to do for now
    
    // 2. Configure the Servo Bounds

        // Configure the Lower and Upper bounds of the servo
        double lower_bound_radians = to_radians( 100 /*std::stod(info_.hardware_parameters["Servo_Lower_Bound_Degrees"])*/ );
        double upper_bound_radians = to_radians( 170 /*std::stod(info_.hardware_parameters["Servo_Upper_Bound_Degrees"])*/ );

        StatusCode servo_bounds_status = m_hardware.set_servo_bounds(lower_bound_radians, upper_bound_radians);

        double center_radians = to_radians( 130 /*std::stod(info_.hardware_parameters["Servo_Center_Degrees"])*/ );

        RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "==============================================");
        RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), std::to_string(to_degrees(lower_bound_radians)).c_str());

        m_hardware.set_servo_center(center_radians);

    if(servo_bounds_status != StatusCode::OK)
        return CallbackReturn::ERROR;

    RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Successfully activated!");

    return CallbackReturn::SUCCESS;

} // end of "on_actiate(const rclcpp_lifecycle::State&)"


CallbackReturn RobotSystemHardware::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
    RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Deactivating ...please wait...");

    m_hardware.close();

    RCLCPP_INFO(rclcpp::get_logger("RobotSystemHardware"), "Successfully deactivated!");

    return CallbackReturn::SUCCESS;

} // end of "on_deactiate(const rclcpp_lifecycle::State&)"


return_type RobotSystemHardware::read(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
    // Nothing to read for now

    return return_type::OK;

} // end of "read(const rclcpp::Time&, const rclcpp::Duration&)"


return_type RobotSystemHardware::write(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{

    double avg_drive = 0;

    for(double d : drive_commands)
    {
        avg_drive += d;
    }

    avg_drive /= 4;

    double avg_steer = 0;

    for(double s : steer_commands)
    {
        avg_steer += s;
    }

    avg_steer /= 2;

    StatusCode drive_status = m_hardware.set_motor(avg_drive);
    StatusCode steer_status = m_hardware.set_servo_percent_from_center(avg_steer);

    StatusCode overall_status = combine_statuses({drive_status, steer_status});

    if(overall_status != StatusCode::OK)
        return return_type::ERROR;

    return return_type::OK;

} // end of "write(const rclcpp::Time&, const rclcpp::Duration&)"


#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  robot_hardware::RobotSystemHardware, SystemInterface)
