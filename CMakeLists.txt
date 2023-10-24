cmake_minimum_required(VERSION 3.8)
project(cpp01_topic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(base_interfaces_demo REQUIRED)

add_executable(minimal_publisher src/talker_str.cpp)
ament_target_dependencies(
  minimal_publisher
  "rclcpp"
  "std_msgs"
)

add_executable(minimal_subscriber src/listener_str.cpp)
ament_target_dependencies(
  minimal_subscriber
  "rclcpp"
  "std_msgs"
)

add_executable(student_publisher src/talker_student.cpp)
ament_target_dependencies(
  student_publisher
  "rclcpp"
  "std_msgs"
  "base_interfaces_demo"
)

add_executable(student_subscriber src/listener_student.cpp)
ament_target_dependencies(
  student_subscriber
  "rclcpp"
  "std_msgs"
  "base_interfaces_demo"
)

install(TARGETS 
  minimal_publisher
  minimal_subscriber
  student_publisher
  student_subscriber
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
