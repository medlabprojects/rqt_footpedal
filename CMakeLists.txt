cmake_minimum_required(VERSION 2.8.3)
project(rqt_footpedal)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rqt_gui
  rqt_gui_cpp
)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(rqt_footpedal_SRCS
	src/rqt_footpedal/FootPedal.cpp
)

set(rqt_footpedal_HDRS
	include/rqt_footpedal/FootPedal.h
)

set(rqt_footpedal_UIS
	src/rqt_footpedal/FootPedal_gui.ui
)

set(rqt_footpedal_INCLUDE_DIRECTORIES
	include
	"${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}"
)

if(NOT EXISTS "${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}")
  file(MAKE_DIRECTORY "${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}")
endif()

catkin_package(
  INCLUDE_DIRS ${rqt_footpedal_INCLUDE_DIRECTORIES}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp
)

qt5_wrap_cpp(rqt_footpedal_MOCS ${rqt_footpedal_HDRS})

# ensure generated header files are being created in the devel space
set(_cmake_current_binary_dir "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_CURRENT_BINARY_DIR "${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}")
qt5_wrap_ui(rqt_footpedal_UIS_H ${rqt_footpedal_UIS})
set(CMAKE_CURRENT_BINARY_DIR "${_cmake_current_binary_dir}")


include_directories(
 	${rqt_footpedal_INCLUDE_DIRECTORIES}
	${catkin_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
)

add_library(
	${PROJECT_NAME}
	${rqt_footpedal_SRCS}
	${rqt_footpedal_MOCS}
	${rqt_footpedal_UIS_H}
)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

find_package(class_loader)
class_loader_hide_library_symbols(${PROJECT_NAME})

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(DIRECTORY 
	include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
