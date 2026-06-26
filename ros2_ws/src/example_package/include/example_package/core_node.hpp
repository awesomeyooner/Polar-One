#ifndef CORE_NODE_HPP
#define CORE_NODE_HPP


#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <cmath>

#include <example_package/example_package_parameters.hpp>


class CoreNode : public rclcpp::Node
{

    public:

        /**
         * @brief Create the ROS 2 Node
         * 
         */
        CoreNode();

        /**
         * @brief Initialize the publishers, subscribers, timers, and params
         * 
         */
        void init();

        /**
         * @brief Shutdown the node
         * 
         */
        void shutdown();

        /**
         * @brief Publish string data
         * 
         */
        void publish_data();

        /**
         * @brief Callback for the subscription
         * 
         * @param message `const std_msgs::msg::String&`
         */
        void on_receive(const std_msgs::msg::String& message);

    private:

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_publisher;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_subscription;

        rclcpp::TimerBase::SharedPtr m_timer;

        std::shared_ptr<example_package::ParamListener> m_param_listener;
        example_package::Params m_params;

        void info(std::string message);


}; // class CoreNode : public rclcpp::Node


#endif // CORE_NODE_HPP