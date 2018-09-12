cmake_minimum_required(VERSION 2.8.3)
project(ros_start)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
)


add_message_files(
  FILES
  Rt1Sensor.msg
  Rt2Sensor.msg
  Key.msg
  )

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

catkin_package(
 INCLUDE_DIRS
 LIBRARIES
 CATKIN_DEPENDS roscpp rospy std_msgs message_runtime geometry_msgs
 DEPENDS
)

add_executable(rosrt_rt1 src/rosrt_rt1.cpp)
target_link_libraries(rosrt_rt1 ${catkin_LIBRARIES})
add_dependencies(rosrt_rt1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(rosrt_rt2 src/rosrt_rt2.cpp)
target_link_libraries(rosrt_rt2 ${catkin_LIBRARIES})
add_dependencies(rosrt_rt2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(rt1_con src/rt1_con.cpp)
target_link_libraries(rt1_con ${catkin_LIBRARIES})
add_dependencies(rt1_con ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(rt1_handle src/rt1_handle.cpp)
target_link_libraries(rt1_handle ${catkin_LIBRARIES})
add_dependencies(rt1_handle ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
