cmake_minimum_required(VERSION 3.8)
project(fsm_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(fsm REQUIRED)
find_package(rclcpp REQUIRED)


# simple_counter
add_executable(simple_counter
  src/simple_counter.cpp
)
set(SOURCES
  src/simple_counter.cpp
)
ament_target_dependencies(simple_counter fsm)
install(
  TARGETS simple_counter
  DESTINATION lib/${PROJECT_NAME}
)

# another_counter
add_executable(another_counter
  src/another_counter.cpp
)
set(SOURCES
  src/another_counter.cpp
)
ament_target_dependencies(another_counter fsm)
install(
  TARGETS another_counter
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
