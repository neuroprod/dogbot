cmake_minimum_required(VERSION 3.10)
set( CMAKE_VERBOSE_MAKEFILE ON )
project(bot)

set(CMAKE_CXX_STANDARD 17)

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )
get_filename_component( BOT_SHARED "${CMAKE_CURRENT_SOURCE_DIR}/../shared" ABSOLUTE )

include_directories( ${BOT_SHARED})

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


set(SRC_FILES
        ${APP_PATH}/src/BotApp.cpp
        ${APP_PATH}/src/SimulationMain.cpp
        ${APP_PATH}/src/RobotMain.cpp
        ${APP_PATH}/src/graph/GraphableArray.cpp
        ${APP_PATH}/src/graph/GraphRenderer.cpp
        ${APP_PATH}/src/motor/Motor.cpp
        ${APP_PATH}/src/motor/MotorControl.cpp
        ${APP_PATH}/src/gui/FBOWindow.cpp
        ${APP_PATH}/src/modelrenderer/ModelRenderer.cpp
        ${APP_PATH}/src/modelrenderer/OrbitCamera.cpp
        ${APP_PATH}/src/modelrenderer/FKModel.cpp
        ${APP_PATH}/src/modelrenderer/FKLeg.cpp
        ${APP_PATH}/src/modelrenderer/FKNode.cpp
        ${APP_PATH}/src/modelrenderer/Mesh.cpp
        ${APP_PATH}/src/modelrenderer/MeshData.cpp
        ${APP_PATH}/src/modelrenderer/MeshDataPool.cpp
        ${APP_PATH}/src/modelrenderer/SymbolBatches.cpp
        ${APP_PATH}/src/ik/IKController.cpp
        ${APP_PATH}/src/ik/IKControleLeg.cpp
        ${APP_PATH}/src/ik/IKLeg.cpp
        ${APP_PATH}/src/ik/IKModel.cpp
        ${APP_PATH}/src/states/StateController.cpp
        ${APP_PATH}/src/states/RiseState.cpp
        ${APP_PATH}/src/states/StepState.cpp
        ${APP_PATH}/src/input/StepInput.cpp
        ${APP_PATH}/src/walking/GaitController.cpp
        ${APP_PATH}/src/walking/LegController.cpp
        )

ci_make_app(
        SOURCES     ${SRC_FILES}
        CINDER_PATH ${CINDER_PATH}

)
target_link_libraries(bot libJetsonGPIO.a)