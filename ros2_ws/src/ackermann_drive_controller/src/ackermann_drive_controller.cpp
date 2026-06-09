#include "ackermann_drive_controller/ackermann_drive_controller.hpp"


using namespace ackermann_drive_controller;
using namespace controller_interface;
using namespace hardware_interface;
using namespace std;


constexpr auto DEFAULT_COMMAND_TOPIC = "~/cmd_vel";
constexpr auto DEFAULT_COMMAND_OUT_TOPIC = "~/cmd_vel_out";


AckermannDriveController::AckermannDriveController() : ControllerInterface() 
{} // end of "AckermannDriveController()"


CallbackReturn AckermannDriveController::on_init()
{
    try
    {
        // Create the parameter listener and get the parameters
        param_listener = make_shared<ParamListener>(get_node());
        params = param_listener->get_params();
    }
    catch (const exception& e)
    {
        fprintf(stderr, "Exception thrown during init stage with message: %s \n", e.what());
        return CallbackReturn::ERROR;
    }

    return CallbackReturn::SUCCESS;

} // end of "on_init()"


InterfaceConfiguration AckermannDriveController::command_interface_configuration() const
{
    vector<string> command_interfaces;

    // Add the drive joint commands (all will be velocity)
    for(const string& joint_name : params.drive_joint_names)
    {
        command_interfaces.push_back(joint_name + "/" + "velocity");
    }

    // Add the steer joint commands (all will be position)
    for(const string& joint_name : params.steer_joint_names)
    {
        command_interfaces.push_back(joint_name + "/" + "position");
    }
    
    return {interface_configuration_type::INDIVIDUAL, command_interfaces};

} // end of "command_interface_configuration()"


InterfaceConfiguration AckermannDriveController::state_interface_configuration() const
{
    vector<string> state_interfaces;

    // There are none for now

    return {interface_configuration_type::INDIVIDUAL, state_interfaces};

} // end of "state_interface_configuration()"

return_type AckermannDriveController::update(const rclcpp::Time& time, const rclcpp::Duration& /* period */)
{
    if(last_command == nullptr)
    {
        return return_type::ERROR;
    }

    double time_since_last_command = abs(
            ((double)last_command->header.stamp.sec + ((double)last_command->header.stamp.nanosec / pow(10, 9))) - time.seconds());

    if(time_since_last_command > params.command_timeout)
    {
        return return_type::ERROR;
    }

    double forward_command = last_command.get()->twist.linear.x;
    double angular_command = last_command.get()->twist.angular.z;

    for(auto interface : drive_interfaces)
    {
        interface.get().set_value(forward_command);
    }

    for(auto interface : steer_interfaces)
    {
        interface.get().set_value(angular_command);
    }

    return return_type::OK;

} // end of update(const rclcpp::Time&, const rclcpp::Duration&)

CallbackReturn AckermannDriveController::on_configure(const rclcpp_lifecycle::State& /* previous_state */)
{
    command_subscriber = get_node()->create_subscription<geometry_msgs::msg::TwistStamped>(
        params.command_topic, rclcpp::SystemDefaultsQoS(),
        [this](const std::shared_ptr<geometry_msgs::msg::TwistStamped> message)
        {
            last_command = message;
        }
    );

    return CallbackReturn::SUCCESS;
}

CallbackReturn AckermannDriveController::on_activate(const rclcpp_lifecycle::State& /* previous_state */)
{
    for(LoanedCommandInterface& interface : command_interfaces_)
    {
        // If this interface is a drive joint
        if(interface.get_prefix_name().find("wheel_joint") != string::npos)
        {
            drive_interfaces.push_back(ref(interface));
            continue;
        }
        // If this interface is a steer joint
        else if(interface.get_prefix_name().find("steer_joint") != string::npos)
        {
            steer_interfaces.push_back(ref(interface));
            continue;
        }
    }

    if(drive_interfaces.size() == 0 || steer_interfaces.size() == 0)
    {
        RCLCPP_INFO(get_node()->get_logger(), "Drive and/or Steer interfaces are empty!");
        return CallbackReturn::ERROR;
    }

    return CallbackReturn::SUCCESS;
}

CallbackReturn AckermannDriveController::on_deactivate(const rclcpp_lifecycle::State& /* previous_state */)
{
    drive_interfaces.clear();
    steer_interfaces.clear();

    return CallbackReturn::SUCCESS;

} // end of "on_deactivate(const rclcpp_lifecycle::State&)"


CallbackReturn AckermannDriveController::on_cleanup(const rclcpp_lifecycle::State& /* previous_state */)
{
    return CallbackReturn::SUCCESS;

} // end of "on_cleanup(const rclcpp_lifecycle::State&)"


CallbackReturn AckermannDriveController::on_error(const rclcpp_lifecycle::State& /* previous_state */)
{
    return CallbackReturn::SUCCESS;

} // end of "on_error(const rclcpp_lifecycle::State&)"


CallbackReturn AckermannDriveController::on_shutdown(const rclcpp_lifecycle::State& /* previous_state */)
{
    return CallbackReturn::SUCCESS;

} // end of "on_shutdown(const rclcpp_lifecycle::State&)"


#include "class_loader/register_macro.hpp"

CLASS_LOADER_REGISTER_CLASS(AckermannDriveController, ControllerInterface)