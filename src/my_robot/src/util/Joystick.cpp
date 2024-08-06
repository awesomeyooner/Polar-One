#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

using std::placeholders::_1;

class Joystick : public rclcpp::Node
{
  public:
  //0 left x 
  //1 left y
  //2 left trigger
  
  //3 right x
  //4 right y
  //5 right trigger
    Joystick() : Node("teleop")
    {
        this->declare_parameter("default_max", rclcpp::PARAMETER_DOUBLE);
        this->declare_parameter("boost_amount", rclcpp::PARAMETER_DOUBLE);
        this->declare_parameter("boost_toggle", rclcpp::PARAMETER_INTEGER);

        // rclcpp::Parameter
        default_max = this->get_parameter("default_max").as_double();
        boost_amount = this->get_parameter("boost_amount").as_double();
        boost_toggle = this->get_parameter("boost_toggle").as_int();

        publisher = this->create_publisher<geometry_msgs::msg::TwistStamped>("cmd_vel", 10);
        subscription = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", 10, std::bind(&Joystick::topic_callback, this, _1));
    }

  private:
    void topic_callback(const sensor_msgs::msg::Joy & msg) const
    {
      //RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg.axes[0]);

      auto twist_stamped = geometry_msgs::msg::TwistStamped();

      twist_stamped.header.frame_id = "command_velocity";
      twist_stamped.header.stamp = this->now();

      double boost_coef;

      if(msg.buttons.at(boost_toggle))
        boost_coef = boost_amount;
      else
        boost_coef = default_max;
        
      twist_stamped.twist.linear.x = msg.axes[1] * boost_coef;
      //twist_stamped.twist.linear.y = msg.axes[0];

      twist_stamped.twist.angular.z = msg.axes[3];

      publisher->publish(twist_stamped);
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription;
    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr publisher;

    double default_max;
    double boost_toggle;
    double boost_amount;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Joystick>());
  rclcpp::shutdown();
  return 0;
}