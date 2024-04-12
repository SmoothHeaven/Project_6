cmake_minimum_required(VERSION 3.8)
project(fun_numbers)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(number_actions REQUIRED)

add_executable(fibonacci_client src/fibonacci_client.cpp)
ament_target_dependencies(fibonacci_client
  rclcpp
  rclcpp_action
  number_actions  # Link against the 'number_actions' package
)

add_executable(fibonacci_server src/fibonacci_server.cpp)
ament_target_dependencies(fibonacci_server
  rclcpp
  rclcpp_action
  number_actions  # Link against the 'number_actions' package
)

install(TARGETS
  fibonacci_server
  fibonacci_client
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
