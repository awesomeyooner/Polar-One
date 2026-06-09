#ifndef ACKERMANN_DRIVE_CONTROLLER_HPP
#define ACKERMANN_DRIVE_CONTROLLER_HPP


#include <chrono>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "rclcpp_lifecycle/state.hpp"

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "controller_interface/controller_interface.hpp"
#include "visibility_control.h"

#include "geometry_msgs/msg/twist_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"


#include "realtime_tools/realtime_box.hpp"
#include "realtime_tools/realtime_publisher.hpp"

#include "tf2_msgs/msg/tf_message.hpp"
#include "tf2_ros/transform_broadcaster.h"

#include "ackermann_drive_controller/ackermann_drive_controller_parameters.hpp"


namespace ackermann_drive_controller
{

    class AckermannDriveController : public controller_interface::ControllerInterface
    {

    public:
        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        AckermannDriveController();

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::InterfaceConfiguration command_interface_configuration() const override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::InterfaceConfiguration state_interface_configuration() const override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::return_type update(const rclcpp::Time &time, const rclcpp::Duration &period) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_init() override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_configure(const rclcpp_lifecycle::State &previous_state) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State &previous_state) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &previous_state) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State &previous_state) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_error(const rclcpp_lifecycle::State &previous_state) override;

        ACKERMANN_DRIVE_CONTROLLER_PUBLIC
        controller_interface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State &previous_state) override;

    protected:

        // ParamListener for yaml config
        std::shared_ptr<ParamListener> param_listener;

        // The struct that holds the yaml config
        Params params;

    };
} // namespace ackermann_drive_controller

#endif