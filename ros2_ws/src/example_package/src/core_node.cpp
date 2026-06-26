#include "example_package/core_node.hpp"


using namespace rclcpp;
using namespace example_package;
using namespace std;
using std::placeholders::_1;

using StringMsg = std_msgs::msg::String;


CoreNode::CoreNode()
    :   Node("example_package") 
    // You would put the node name but to keep it simple
    // I'm just going to have it as the package name 
{} // end of "CoreNode()"


void CoreNode::init()
{
    info("Initializing...");

    // You can use params with
    // m_params.my_bool

    m_param_listener = std::make_shared<ParamListener>(this);
    m_params = m_param_listener->get_params();

    m_publisher = this->create_publisher<StringMsg>(
        "my_topic_name", 
        SystemDefaultsQoS()
    );

    // Create with an explicit method
    m_subscription = this->create_subscription<StringMsg>(
        "my_topic_name", 
        SystemDefaultsQoS(),
        bind(&CoreNode::on_receive, this, _1)
    );

    // Create using a lambda function
    // m_subscription = this->create_subscription<StringMsg>(
    //     "my_topic_name", 
    //     SystemDefaultsQoS(),
    //     [this](const StringMsg& /*message*/) 
    //     {
    //         // Do stuff here...
    //     }
    // );

    m_timer = this->create_wall_timer(
        chrono::milliseconds(100), // Publish every 100ms
        bind(&CoreNode::publish_data, this)
    );

    info("Finished Initializing!");

} // end of "init()"


void CoreNode::shutdown()
{
    info("Shutting down...");

} // end of "shutdown()"


void CoreNode::publish_data()
{
    rclcpp::Time now = this->now();

    string text_to_send = "Hello World! " + to_string(now.seconds());

    StringMsg message = StringMsg();
        message.data = text_to_send;

    m_publisher->publish(message);

} // end of "publish_data()"


void CoreNode::on_receive(const StringMsg& message)
{
    info("Received message: " + message.data); 

} // end of "on_receive(const StringMsg&)"


void CoreNode::info(string message)
{
    RCLCPP_INFO(this->get_logger(), message.c_str());

} // end of "info(string)"

