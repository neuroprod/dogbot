//
// Created by kris on 22.07.20.
//
#include "cinder/gl/gl.h"
#include "SimulationMain.h"
#include "cinder/CinderImGui.h"
#include "graph/GraphRenderer.h"
#include "graph/GraphableArray.h"
using namespace ci;
using namespace ci::app;
void SimulationMain::setup() {
    ImGui::Initialize();
    setWindowSize(windowSizeX->value(),windowSizeY->value());
    setWindowPos(0,0);
    test.prepGraph("test",1,{50},{Color(1,0,1)},{"sin"} );

    GRAPH()->reg(&test);
}
void SimulationMain::update() {

    test.addData({sinf((float)getElapsedSeconds())});

}
void SimulationMain::draw() {

    gl::clear();
    GRAPH()->draw();

}