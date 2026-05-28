import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([

        launch_ros.actions.Node(
            package='lane_detector',
            executable='detector_node',
            name='detector_node',
            ),
            #('/cmd_vel', '/diffbot_base_controller/cmd_vel')
  ])