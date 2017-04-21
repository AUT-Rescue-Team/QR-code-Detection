# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(test)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} opencv)


add_executable(qrcode src/main.cpp)
target_link_libraries(qrcode ${catkin_LIBRARIES} zbar opencv_highgui opencv_core opencv_imgproc)
add_dependencies(qrcode test_generate_messages_cpp)

# %EndTag(FULLTEXT)%

