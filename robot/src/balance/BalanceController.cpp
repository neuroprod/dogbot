//
// Created by kris on 09.09.20.
//

#include "BalanceController.h"
#include "cinder/CinderImGui.h"
#include "../graph/GraphRenderer.h"

void BalanceController::setup( bool isRobot)
{

    pidX.Kp = 0;
    pidX.Ki = 0;
    pidX.Kd = 0;
    pidX.inv =false;
    pidX.max =50;
    pidX.min =-50;
    pidZ.Kp = 0;
    pidZ.Ki = 0;
    pidZ.Kd = 0;
    pidZ.inv = true;
    balanceGraph.prepGraph("Balance","simulation",2,{1000,1000},{ci::Color(1,0,0),ci::Color(0,1,0)},{"rotX","rotZ"} );
    balanceGraph.gVisible =true;
    balanceGraph.drawZero =true;
    GRAPH()->reg(&balanceGraph);
}
void BalanceController::update(float rotX,float rotZ)
{
   // offsetX =  pidZ.calculate(0, rotZ);
   // offsetZ = pidX.calculate(0, tan(rotX)*300);

    balanceGraph.addData({rotX,rotZ});
}
void BalanceController::reset()
{
    pidX.reset();
    pidZ.reset();

}
void BalanceController::drawGui()
{
    ImGui::Begin("Balance");
    pidX.drawGui("xRotation");
    pidZ.drawGui("zRotation");
    ImGui::End();

}


