import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='joy',
            executable='joy_node',
            name='joystick_driver'),

        launch_ros.actions.Node(
            package='my_robot',
            executable='joystick_teleop',
            name='joystick_teleop',
            )

            #('/cmd_vel', '/diffbot_base_controller/cmd_vel')
  ])