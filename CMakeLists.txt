cmake_minimum_required(VERSION 2.8.3)
project(ardrone_command_gui)

#Get c++11
ADD_DEFINITIONS(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy

  std_msgs
  message_generation
  ardrone_autonomy
  sensor_msgs
  cv_bridge
  ardrone_command
)

#QT stuff
#Access QT5 package
find_package(Qt5Widgets)

#Make moc called as nessisary
set(CMAKE_AUTOMOC ON)


#include_directories(include)

#include_directories('/home/hewhosurvives/c++/randomProjects/ros/catkin_ws/devel/include/' 'opt/ros/indigo/include/usr/include')

FILE(GLOB SOURCEFILES src/*.cpp src/*.c)
FILE(GLOB HEADERS src/*.hpp src/*.h ${QT_USE_FILE} ${QT_HEADERS})

#Add the QT modules we are going to use
#QT_USE_QTNETWORK QT_USE_QTOPENGL QT_USE_QTSQL QT_USE_QTXML QT_USE_QTSVG QT_USE_QTTEST QT_USE_QTDBUS QT_USE_QTSCRIPT QT_USE_QTWEBKIT QT_USE_QTXMLPATTERNS QT_USE_PHONON
SET(QT_USE_QTCORE TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#List all of the sources and all the headers
SET(my_SOURCES ${SOURCEFILES})
SET(my_HEADERS ${HEADERS})

#List all of the .ui forms and resources that need to be processed
SET(my_FORMS src/ardroneCommandGuiTemplate.ui)
#SET(my_RESOURCES democracyResources.qrc)

#Set the headers to be processed by moc
#QT5_WRAP_CPP(my_HEADERS_MOC ${my_HEADERS})


#Set the UIs and resources to be processed
QT5_WRAP_UI(my_FORMS_HEADERS ${my_FORMS})
#QT5_ADD_RESOURCES(my_RESOURCES_RCC ${my_RESOURCES})

#include QT headers


#Add QT definitions
ADD_DEFINITIONS(${QT_DEFINITIONS})


#Add all of the generated files to the include
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CATKIN_DEVEL_PREFIX}/ardrone_command ${catkin_INCLUDE_DIRS} ${ardrone_command_INCLUDE_DIRS} ${ARDRONE_COMMAND_INCLUDE_DIR})





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
#  LIBRARIES beginner_tutorials
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
CATKIN_DEPENDS message_runtime ardrone_autonomy ardrone_command
)




###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)



## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(beginner_tutorials_node beginner_tutorials_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(beginner_tutorials_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS beginner_tutorials beginner_tutorials_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_beginner_tutorials.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

#message('Yowser' ${ardrone_autonomy_INCLUDE_DIRS})
# Add headers directory


add_executable(ardrone_command_gui ${my_SOURCES} ${my_HEADERS_MOC} ${my_FORMS_HEADERS} ${my_RESOURCES_RCC})
target_link_libraries(ardrone_command_gui ${catkin_LIBRARIES} zbar opencv_core opencv_highgui opencv_calib3d procps Qt5::Widgets)


#add_dependencies(talker ${catkin_EXPORTED_TARGETS})

