from launch import LaunchDescription
from launch.actions import ExecuteProcess

def generate_launch_description():
    ros2_setup_path = '/opt/ros/humble/setup.bash'
    workspace_setup_path = '/home/thien/Documents/IE_ROS/Project_6/install/setup.bash'
    return LaunchDescription([
        ExecuteProcess(
            cmd=[
                'gnome-terminal', '--', 'bash', '-c', 
                f'source {ros2_setup_path} && source {workspace_setup_path} && ros2 run fun_numbers fibonacci_server; echo "Press Enter to continue..."; read'
            ],
            output='screen'
        ),
        ExecuteProcess(
            cmd=[
                'gnome-terminal', '--', 'bash', '-c', 
                f'source {ros2_setup_path} && source {workspace_setup_path} && ros2 run fun_numbers fibonacci_client --ros-args -p order:=10; echo "Press Enter to continue..."; read'
            ],
            output='screen'
        )
    ])



