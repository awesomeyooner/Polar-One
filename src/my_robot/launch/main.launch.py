import launch
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os

from ament_index_python.packages import get_package_share_directory

from launch_ros.actions import Node

def generate_launch_description():

    carbot_hardware_interface_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/example_11/bringup/launch/carlikebot.launch.py')
    )

    controller_manager_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/example_11/bringup/launch/controller_manager.launch.py')
    )

    robot_state_publisher_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/example_11/bringup/launch/robot_state_publisher.launch.py'),
        launch_arguments={'use_sim_time': 'false'}.items()
    )

    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    )

    robot_bicycle_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            # "effort_controllers",
            # "-c", "/controller_manager",
            # "-t", "effort_controllers/JointGroupEffortController", 
            "effort_controller",
            "--controller-manager", 
            "/controller_manager"
            ],
    )

    joystick_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/my_robot/launch/joystick.launch.py')
    )

    mux_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/my_robot/launch/twist_mux.launch.py')
    )

    translator_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/my_robot/launch/effort_translator.launch.py')
    )

    camera_driver_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource('src/lane_detector/launch/camera_driver.launch.py')
    )
    # component2_launch = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource('component2.launch.py')
    # )

    return LaunchDescription([
        #diffbot_hardware_interface_launch,
        #carbot_hardware_interface_launch,
        controller_manager_launch,
        robot_state_publisher_launch,
        joint_state_broadcaster_spawner,
        robot_bicycle_controller_spawner,

        joystick_launch,
        translator_launch,
        camera_driver_launch

        # component2_launch,
        # Add any additional launch files or actions here
    ])