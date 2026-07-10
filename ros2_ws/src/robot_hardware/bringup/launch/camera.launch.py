import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration, Command
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch_ros.actions import Node

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler
from launch.conditions import IfCondition, UnlessCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, PathJoinSubstitution, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

import xacro

def generate_launch_description():
    
    # CHANGE ME
    package = "robot_hardware"

    # CHANGE ME
    params_file = os.path.join(get_package_share_directory(package), 'config','camera_driver.yaml')

    launch_file = os.path.join(
        get_package_share_directory("camera_driver"),
        "launch",
        "camera_driver.launch.py"
    )

    camera_driver_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(launch_file),
        launch_arguments={
            "params_file": params_file
        }.items()
    )

    nodes = [
        camera_driver_launch
    ]

    return LaunchDescription(nodes)
