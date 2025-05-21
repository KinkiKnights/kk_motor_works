cmake_minimum_required(VERSION 3.8)
project(motor_works)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(kk_driver_msg REQUIRED)

## 
add_executable(motor_works src/main.cpp)
ament_target_dependencies(motor_works std_msgs sensor_msgs rclcpp kk_driver_msg)

install(TARGETS
  motor_works
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
