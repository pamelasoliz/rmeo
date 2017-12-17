cmake_minimum_required(VERSION 2.8.3)
project(mybot_codigo)

find_package(catkin REQUIRED
	#rospy

  roscpp
  urdf
  tf
  nav_msgs
  message_generation
  std_msgs
  actionlib
  
)

#find_package(Eigen REQUIRED)
#find_package(Boost REQUIRED thread)

#link_directories(${Boost_LIBRARY_DIRS})
link_directories(${catkin_LIBRARY_DIRS})

catkin_package()

#include_directories(SYSTEM ${EIGEN_INCLUDE_DIRS} & ${Boost_INCLUDE_DIRS})
# include
include_directories(${catkin_INCLUDE_DIRS})

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

add_executable(puntoAB src/puntoAB.cpp)
add_dependencies(puntoAB puntoAB_generate_messages_cpp)
target_link_libraries(puntoAB ${catkin_LIBRARIES})


