import launch
import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    current_dir = os.getcwd()
    print(f"Current directory: {current_dir}") 
    # 声明参数文件路径的启动参数
    return LaunchDescription([
        DeclareLaunchArgument(
            'config_file',
            default_value='/home/han/ros_ws/src/shijuepub/config/params.yaml',
            description='Path to the YAML parameter file'
        ),
        Node(
            package='shijuepub',  
            executable='pub',  
            name='pub', 
            output='screen',
            parameters=[LaunchConfiguration('config_file')], 
        ),
        LogInfo(
            condition=launch.conditions.LaunchConfigurationEquals('config_file', ''),
            msg="Starting with default parameter file"
        )
    ])


