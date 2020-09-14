//
// Created by kris on 09.09.20.
//

#include "BalanceController.h"
#include "cinder/CinderImGui.h"
#include "../graph/GraphRenderer.h"

void BalanceController::setup( bool isRobot)
{
   // SETTINGS()->getFloat("RobotSettings","bodyY",300)
    pidX.Kp = 120;
    pidX.Ki = 0;
    pidX.Kd = 34;
    pidX.inv =false;
    pidZ.Kp = 80;
    pidZ.Ki = 1.7;
    pidZ.Kd = 0;
    pidZ.inv = true;
    balanceGraph.prepGraph("Balance","simulation",2,{1000,1000},{ci::Color(1,0,0),ci::Color(0,1,0)},{"rotX","rotZ"} );
    balanceGraph.gVisible =true;
    balanceGraph.drawZero =true;
    GRAPH()->reg(&balanceGraph);
}
void BalanceController::update(float rotX,float rotZ)
{
    offsetX =  pidZ.calculate(0, rotZ);
    offsetZ = pidX.calculate(0, rotX);

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


