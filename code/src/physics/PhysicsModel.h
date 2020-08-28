//
// Created by kris on 26.08.20.
//

#ifndef BOT_PHYSICSMODEL_H
#define BOT_PHYSICSMODEL_H

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h"
#include "BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h"
#include "BulletDynamics/Featherstone/btMultiBodyPoint2Point.h"
#include "BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointMotor.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointFeedback.h"

class PhysicsModel
{
public:
    PhysicsModel(){}
    void setup();

    btMultiBody* mMultiBody =nullptr;
};


#endif //BOT_PHYSICSMODEL_H
