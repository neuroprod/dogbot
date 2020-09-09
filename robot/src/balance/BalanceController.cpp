//
// Created by kris on 09.09.20.
//

#include "BalanceController.h"
#include "cinder/CinderImGui.h"
void BalanceController::setup( bool isRobot)
{
   // SETTINGS()->getFloat("RobotSettings","bodyY",300)
    pidX.Kp = 0;
    pidX.Kd = 0;
    pidX.inv = true;
    pidZ.Kp = 1000;
    pidZ.Kd = 0;

}
void BalanceController::update(float rotX,float rotZ)
{
    offsetX =  pidZ.calculate(0, rotZ);
    offsetZ = pidX.calculate(0, rotX);


}
void BalanceController::drawGui()
{
    ImGui::Begin("Balance");
    pidX.drawGui("xRotation");
    pidZ.drawGui("zRotation");
    ImGui::End();
}


