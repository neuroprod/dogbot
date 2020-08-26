//
// Created by kris on 26.08.20.
//

#include "PhysicsController.h"

void PhysicsController::setup()
{




   world.setup();
    model.setup();

   floor.setup();
   world.m_dynamicsWorld->addRigidBody(floor.body);

}
void PhysicsController::update()
{
   world.update();

}

void PhysicsController::reset()
{


}
void PhysicsController::drawGui(){}