cmake_minimum_required (VERSION 2.8)
project (cloud)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

find_package(OpenCV REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

add_definitions(-std=c++11)

create_rapp(
    NAME ${PROJECT_NAME}
    SRCS main.cpp
    LIBS ${OpenCV_LIBS}
)
