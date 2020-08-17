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
   // ImGui::Initialize();
    setWindowSize(windowSizeX->value(),windowSizeY->value());
    setWindowPos(0,0);

    modelRenderer.setup();

    test.prepGraph("test graph",1,{100},{Color(1,0,0)},{"sin"} );
    test2.prepGraph("test graph2",1,{100},{Color(0,1,1)},{"cos"} );
    GRAPH()->reg(&test);
    GRAPH()->reg(&test2);
}
void SimulationMain::update() {

    modelRenderer.update();
    test.addData({sinf((float)getElapsedSeconds())});
    test2.addData({cosf((float)getElapsedSeconds())});
}
void SimulationMain::draw() {

    modelRenderer.draw();
    GRAPH()->draw();

}