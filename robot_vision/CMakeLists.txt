cmake_minimum_required (VERSION 2.8)
project (rapp_vision)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

#message("RAPP: ${Rapp_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

create_rapp(
	NAME rapp_vision
	SRCS main.cpp
)
