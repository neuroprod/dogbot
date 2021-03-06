cmake_minimum_required(VERSION 3.10)
set( CMAKE_VERBOSE_MAKEFILE ON )
project(remote)

set(CMAKE_CXX_STANDARD 17)


get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )


include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


set(SRC_FILES
        ${APP_PATH}/src/RemoteApp.cpp
        ${APP_PATH}/src/gui/GuiSetup.cpp
        ${APP_PATH}/src/serialInput/RSerial.cpp
        ${APP_PATH}/src/serialInput/Joystick.cpp
        ${APP_PATH}/src/communication/Communication.cpp
        ${APP_PATH}/src/communication/OSCReceiver.cpp
        ${APP_PATH}/src/communication/OSCSender.cpp
        )


ci_make_app(
        SOURCES     ${SRC_FILES}
        CINDER_PATH ${CINDER_PATH}
        BLOCKS OSC
)


target_link_libraries(remote stdc++fs)
