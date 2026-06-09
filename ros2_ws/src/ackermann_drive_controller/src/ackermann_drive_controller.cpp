#include "ackermann_drive_controller/ackermann_drive_controller.hpp"


namespace
{
    constexpr auto DEFAULT_COMMAND_TOPIC = "~/cmd_vel";
    constexpr auto DEFAULT_COMMAND_OUT_TOPIC = "~/cmd_vel_out";
    constexpr auto DEFAULT_ODOMETRY_TOPIC = "~/odom";
    constexpr auto DEFAULT_TRANSFORM_TOPIC = "/tf";
}


using namespace ackermann_drive_controller;
using namespace controller_interface;
using namespace std;


    AckermannDriveController::AckermannDriveController() : ControllerInterface() {}

    CallbackReturn AckermannDriveController::on_init()
    {
        try
        {
            // Create the parameter listener and get the parameters
            param_listener = make_shared<ParamListener>(get_node());
            params = param_listener->get_params();
        }
        catch (const exception &e)
        {
            fprintf(stderr, "Exception thrown during init stage with message: %s \n", e.what());
            return CallbackReturn::ERROR;
        }

        return CallbackReturn::SUCCESS;
    }

    InterfaceConfiguration AckermannDriveController::command_interface_configuration() const
    {

        return {interface_configuration_type::INDIVIDUAL, {}};
    }

    InterfaceConfiguration AckermannDriveController::state_interface_configuration() const
    {

        return {interface_configuration_type::INDIVIDUAL, {}};
    }

    return_type AckermannDriveController::update(const rclcpp::Time& /* time */, const rclcpp::Duration& /* period */)
    {

        return return_type::OK;
    }

    CallbackReturn AckermannDriveController::on_configure(const rclcpp_lifecycle::State& /* previous_state */)
    {
        
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn AckermannDriveController::on_activate(const rclcpp_lifecycle::State& /* previous_state */)
    {

        return CallbackReturn::SUCCESS;
    }

    CallbackReturn AckermannDriveController::on_deactivate(const rclcpp_lifecycle::State& /* previous_state */)
    {
    
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn AckermannDriveController::on_cleanup(const rclcpp_lifecycle::State& /* previous_state */)
    {
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn AckermannDriveController::on_error(const rclcpp_lifecycle::State& /* previous_state */)
    {
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn AckermannDriveController::on_shutdown(const rclcpp_lifecycle::State& /* previous_state */)
    {
        return CallbackReturn::SUCCESS;
    }


#include "class_loader/register_macro.hpp"

CLASS_LOADER_REGISTER_CLASS(AckermannDriveController, ControllerInterface)