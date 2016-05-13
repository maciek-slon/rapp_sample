cmake_minimum_required (VERSION 2.8)
project (rapp_navigation)

find_package(Rapp REQUIRED)
find_package(RappRobots REQUIRED)

#message("RAPP: ${Rapp_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

setup_rapp()

create_rapp(
	NAME rapp_navigation
	LIBS rapp_robot_localization rapp_robot_info
	SRCS main.cpp
)
install(FILES
example_qr_map.xml
DESTINATION ${CMAKE_INSTALL_PREFIX}/share/rapp_navigation
)
