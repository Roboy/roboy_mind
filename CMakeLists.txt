cmake_minimum_required(VERSION 2.8.3)
project(roboy_mind)

set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation  
  json_prolog
  knowrob_actions
  knowrob_map_data
  knowrob_map_tools
  rosjava_bootstrap
  rosjava_build_tools
  rosjava_messages
)


## Generate services in the 'srv' folder
add_service_files(
   DIRECTORY
    srv
   FILES
    srvAssertProperty.srv
    srvCallQuery.srv
    srvCheckProperty.srv
    srvCheckQuery.srv
    srvCreateInstance.srv
    srvFindInstances.srv
    srvShowInstances.srv
    srvShowProperty.srv
    srvShowPropertyValue.srv

    srvSaveObject.srv
    srvGetObject.srv
 )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES tumgo_control
   CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

## Declare a C++ library
# add_library(tumgo_control
#   src/${PROJECT_NAME}/tumgo_control.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(tumgo_control ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
add_executable(reasoning_node src/reasoning_node.cpp)
add_dependencies(reasoning_node roboy_mind_generate_messages_cpp)
target_link_libraries(reasoning_node  ${catkin_LIBRARIES})

#############
## Install ##
#############

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination

## Mark other files for installation (e.g. launch and bag files, etc.)
 install(DIRECTORY launch config
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
