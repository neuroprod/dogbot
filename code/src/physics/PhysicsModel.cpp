//
// Created by kris on 26.08.20.
//

#include "PhysicsModel.h"
#include "../RobotSettings.h"
void ::PhysicsModel::setup()
{

    int numLinks = 16;

    float posY = 0;
    btVector3 baseHalfExtents(BOTSETTINGS()->bodyLength/ 2000.f, 80.0f / 2000.f, BOTSETTINGS()->bodyWidth / 2000.f);

    btVector3 basePosition = btVector3(0.f, posY, 0.f);

    btVector3 baseInertiaDiag(0.f, 0.f, 0.f);
    float baseMass = 6;
    if (baseMass)
    {
        btCollisionShape* shape = new btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));
        shape->calculateLocalInertia(baseMass, baseInertiaDiag);
        delete shape;
    }
    mMultiBody = new btMultiBody(numLinks, baseMass, baseInertiaDiag, false, false);
    btQuaternion baseOriQuat(0.f, 0.f, 0.f, 1.f);

    mMultiBody->setBasePos(basePosition);
    mMultiBody->setWorldToBaseRot(baseOriQuat);

}