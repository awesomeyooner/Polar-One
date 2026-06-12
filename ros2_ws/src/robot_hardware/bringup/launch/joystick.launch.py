import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration, Command
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler
from launch.conditions import IfCondition, UnlessCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

import xacro

def generate_launch_description():
    
    package = "robot_hardware"

    joy_params = os.path.join(get_package_share_directory(package),'config','joystick.yaml')

    joy_node = Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            parameters=[joy_params]
            )
    
    joystick_driver_node = Node(
            package='joystick_driver',
            executable='joystick_teleop',
            name='joystick_teleop',
            parameters=[joy_params]
            )

    nodes = [
        joy_node,
        joystick_driver_node
    ]

    return LaunchDescription(nodes)
