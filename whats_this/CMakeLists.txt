cmake_minimum_required (VERSION 2.8)
project (whats_this)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

find_package(OpenCV REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

FILE(GLOB MODELS "models/*.jpg")
FILE(GLOB TEAS "teas/*.png")

create_rapp(
    NAME ${PROJECT_NAME}
    SRCS main.cpp
    LIBS ${OpenCV_LIBS}
    FILES ${MODELS} ${TEAS}
)
