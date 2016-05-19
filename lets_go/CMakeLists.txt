cmake_minimum_required (VERSION 2.8)
project (lets_go)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

create_rapp(
    NAME ${PROJECT_NAME}
    SRCS main.cpp
    FILES maps/empty.yaml maps/empty.png
)
