//
// Created by kris on 09.09.20.
//

#include "BalanceController.h"
#include "cinder/CinderImGui.h"
#include "../graph/GraphRenderer.h"

void BalanceController::setup( bool isRobot)
{

    pidX.Kp = 1;
    pidX.Ki = 0;
    pidX.Kd = 0;
    pidX.inv =false;
    pidX.max =50;
    pidX.min =-50;
    //
    pidZ.Kp = 3;
    pidZ.Ki = 0;
    pidZ.Kd = 0;
    pidZ.inv = true;
    pidZ.max =50;
    pidZ.min =-50;
    balanceGraph.prepGraph("Balance","robot",2,{1,1},{ci::Color(1,0,0),ci::Color(0,1,0)},{"rotX","rotZ"} );
    balanceGraph.gVisible =true;
    balanceGraph.drawZero =true;
    GRAPH()->reg(&balanceGraph);
}
void BalanceController::update(float rotX,float rotZ)
{
    inputX = rotX;
    inputZ = rotZ;

    float adjX = inputX-offsetX;
    float adjZ = inputZ-offsetZ;
    if(adjX >30 ||adjX <-30   ){return;}
    if(adjZ >30 ||adjZ <-30   ){return;}
    balanceZ =  pidX.calculate(0, adjX );
    balanceX = pidZ.calculate(0, adjZ);

    balanceGraph.addData({rotX,rotZ});
}
void BalanceController::setLevel()
{
    offsetX =   inputX;
    offsetZ =   inputZ;

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


