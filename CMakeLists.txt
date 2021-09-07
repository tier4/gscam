cmake_minimum_required(VERSION 3.5)

project(gscam)

# System Dependencies
find_package(PkgConfig)

pkg_check_modules(GSTREAMER QUIET gstreamer-0.10)
if(NOT GSTREAMER_FOUND)
  set(GSTREAMER_VERSION_1_x TRUE)
endif()
if(GSTREAMER_VERSION_1_x)
  message(STATUS "gst 1.0")
  pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
  pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
else()
  message(STATUS "gst 0.1")
  pkg_check_modules(GSTREAMER REQUIRED gstreamer-0.10)
  pkg_check_modules(GST_APP REQUIRED gstreamer-app-0.10)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(gscam SHARED
  src/gscam.cpp
)

target_include_directories(gscam
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${GLIB_INCLUDE_DIRS}
    ${GST_APP_INCLUDE_DIRS}
)

target_link_libraries(gscam
  ${GSTREAMER_LIBRARIES}
  ${GST_APP_LIBRARIES}
)

rclcpp_components_register_node(gscam
  PLUGIN "gscam::GSCam"
  EXECUTABLE gscam_node
)

ament_auto_package(
  INSTALL_TO_SHARE
    examples
)
