cmake_minimum_required(VERSION 3.0.2)
project(path_planning)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)


set(CMAKE_AUTOMOC ON) #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON) #this needs to be on so cmake will know what to do with QT resource Files
#set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Eigen3 REQUIRED)

set(QT_LIBRARIES Qt5::Widgets)


include_directories(${PROJECT_SOURCE_DIR}/Sources/)
include_directories(${PROJECT_SOURCE_DIR}/Headers/)
include_directories(${PROJECT_SOURCE_DIR}/Forms/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

SET(SOURCES 
        ${PROJECT_SOURCE_DIR}/Sources/main.cpp
        ${PROJECT_SOURCE_DIR}/Sources/mainwindow.cpp
        ${PROJECT_SOURCE_DIR}/Sources/discrete_env.cpp
        ${PROJECT_SOURCE_DIR}/Sources/continuous_env.cpp
        ${PROJECT_SOURCE_DIR}/Sources/discrete_node.cpp)

SET(HEADERS 
        ${PROJECT_SOURCE_DIR}/Headers/mainwindow.h
        ${PROJECT_SOURCE_DIR}/Headers/discrete_env.h
        ${PROJECT_SOURCE_DIR}/Headers/continuous_env.h
        ${PROJECT_SOURCE_DIR}/Headers/discrete_node.h)
        
SET(FORMS ${PROJECT_SOURCE_DIR}/Forms/mainwindow.ui)


QT5_WRAP_CPP(HEADERS_MOC ${HEADERS})
QT5_WRAP_UI(FORMS_HEADERS ${FORMS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${HEADERS_MOC} ${FORMS_HEADERS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
