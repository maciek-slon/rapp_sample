cmake_minimum_required (VERSION 2.8)
project (talk_to_me)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

create_rapp(
    NAME talk_to_me
    SRCS main.cpp 
    FILES cheer.wav
)
