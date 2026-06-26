cmake_minimum_required(VERSION 3.8)
project(ackermann_drive_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_BUILD_RPATH "$ENV{HOME}/anaconda3/lib")
set(CMAKE_INSTALL_RPATH "$ENV{HOME}/anaconda3/lib") 

# Add Packages
set(THIS_PACKAGE_INCLUDE_DEPENDS
  ament_cmake
  backward_ros

  control_toolbox
  controller_interface
  generate_parameter_library
  geometry_msgs
  hardware_interface
  nav_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  rcpputils
  realtime_tools
  tf2
  tf2_msgs
  tf2_ros
  tf2_geometry_msgs
)

# Find each Package
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

# Generate Parameter Library
generate_parameter_library(${PROJECT_NAME}_parameters
  src/${PROJECT_NAME}_parameters.yaml
  include/${PROJECT_NAME}/custom_validators.hpp
)

add_library(${PROJECT_NAME} SHARED
    src/ackermann_drive_controller.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
  /opt/ros/jazzy/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${PROJECT_NAME}_parameters
    rclcpp::rclcpp
)

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

ament_target_dependencies(${PROJECT_NAME} PUBLIC ${THIS_PACKAGE_INCLUDE_DEPENDS})
pluginlib_export_plugin_description_file(controller_interface ${PROJECT_NAME}_plugin.xml)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_parameters
  EXPORT export_${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

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

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()