cmake_minimum_required(VERSION 3.10)
set( CMAKE_VERBOSE_MAKEFILE ON )
project(bot)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenZen REQUIRED)
find_package( Bullet REQUIRED )
include_directories(${BULLET_INCLUDE_DIR} )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE )


include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


set(SRC_FILES
        ${APP_PATH}/src/Status.cpp
        ${APP_PATH}/src/BotApp.cpp
        ${APP_PATH}/src/Simulation.cpp
        ${APP_PATH}/src/Robot.cpp
        ${APP_PATH}/src/graph/GraphableArray.cpp
        ${APP_PATH}/src/graph/GraphRenderer.cpp
        ${APP_PATH}/src/motor/Motor.cpp
        ${APP_PATH}/src/motor/MotorControl.cpp
        ${APP_PATH}/src/gui/FBOWindow.cpp
        ${APP_PATH}/src/gui/GuiSetup.cpp
        ${APP_PATH}/src/gui/Logger.cpp
        ${APP_PATH}/src/gui/SoundHandler.cpp
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
        ${APP_PATH}/src/states/states/StandUpState.cpp
        ${APP_PATH}/src/states/states/LayDownState.cpp
        ${APP_PATH}/src/states/states/StepState.cpp
        ${APP_PATH}/src/states/states/Test2LegsUpState.cpp
        ${APP_PATH}/src/states/states/TestAllLegsDownState.cpp
        ${APP_PATH}/src/input/StepInput.cpp
        ${APP_PATH}/src/walking/GaitController.cpp
        ${APP_PATH}/src/walking/LegController.cpp
        ${APP_PATH}/src/physics/Conv.cpp
        ${APP_PATH}/src/physics/PhysicsController.cpp
        ${APP_PATH}/src/physics/PhysicsWorld.cpp
        ${APP_PATH}/src/physics/PhysicsModel.cpp
        ${APP_PATH}/src/physics/PhysicsLeg.cpp
        ${APP_PATH}/src/balance/IMU.cpp
        ${APP_PATH}/src/balance/PID.cpp
        ${APP_PATH}/src/balance/BalanceController.cpp
        ${APP_PATH}/src/communication/OSCSender.cpp
        ${APP_PATH}/src/communication/OSCReceiver.cpp
        ${APP_PATH}/src/communication/Communication.cpp
        )
ci_make_app(
        SOURCES     ${SRC_FILES}
        CINDER_PATH ${CINDER_PATH}
        BLOCKS OSC
)
target_link_libraries(bot  OpenZen::OpenZen ${BULLET_LIBRARIES})

