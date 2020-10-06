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
    //
    pidZ.Kp = 0;
    pidZ.Ki = 0;
    pidZ.Kd = 0;
    pidZ.inv = true;
    pidZ.max =50;
    pidZ.min =-50;



    pidAVX.Kp = 0;
    pidAVX.Ki = 0;
    pidAVX.Kd = 0;
    pidAVX.inv =true;
    pidAVX.max =50;
    pidAVX.min =-50;
    //
    pidAVZ.Kp = 0;
    pidAVZ.Ki = 0;
    pidAVZ.Kd = 0;
    pidAVZ.inv = false;
    pidAVZ.max =50;
    pidAVZ.min =-50;



    balanceGraph.prepGraph("Balance","robot",6,{1,1,0.5,0.5,2,2},{ci::Color(1,0,0),ci::Color(0,1,0),ci::Color(0.5,0,0),ci::Color(0,0.5,0),ci::Color(1,1,1),ci::Color(0.5,0.5,0.5)},{"rotX","rotZ","avX","avZ","balX","balZ"} );
    balanceGraph.gVisible =true;
    balanceGraph.drawZero =true;
    GRAPH()->reg(&balanceGraph);
}
void BalanceController::update(float rotX,float rotZ,float avX,float avZ)
{
    inputX = rotX;
    inputZ = rotZ;

    float adjX = inputX-offsetX;
    float adjZ = inputZ-offsetZ;

    balanceZ =  pidX.calculate(0, adjX )+pidAVX.calculate(0, avX );;
    balanceX = pidZ.calculate(0, adjZ)+pidAVZ.calculate(0, avZ );;

    balanceGraph.addData({rotX,rotZ,avX,avZ,balanceX,balanceZ});
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
    pidAVX.drawGui("xAngVel");
    pidZ.drawGui("zRotation");
    pidAVZ.drawGui("zAngVel");
    ImGui::End();

}


