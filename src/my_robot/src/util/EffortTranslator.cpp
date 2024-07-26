#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using std::placeholders::_1;

class EffortTranslator : public rclcpp::Node
{
  public:
 
    EffortTranslator() : Node("translator")
    {
        publisher = this->create_publisher<std_msgs::msg::Float64MultiArray>("effort_controller/commands", 10);
        subscription = this->create_subscription<geometry_msgs::msg::TwistStamped>(
        "cmd_vel", 10, std::bind(&EffortTranslator::topic_callback, this, _1));
    }

  private:
    void topic_callback(const geometry_msgs::msg::TwistStamped & msg) const
    {
      //RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg.axes[0]);

      std_msgs::msg::Float64MultiArray translated_command = std_msgs::msg::Float64MultiArray();

      translated_command.data.push_back(msg.twist.linear.x);
      translated_command.data.push_back(msg.twist.angular.z);

      publisher -> publish(translated_command);
    }

    rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr subscription;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EffortTranslator>());
  rclcpp::shutdown();
  return 0;
}