//
// Created by kris on 26.08.20.
//

#include "PhysicsController.h"

void PhysicsController::setup(  ci::mat4 defaultmatrix ,std::vector<float>  defaultAngles)
{




   world.setup();
   floor.setup();
   world.m_dynamicsWorld->addRigidBody(floor.body);

model.setDefaultAngles(defaultmatrix , defaultAngles);
   model.setup(world.m_dynamicsWorld);



}
void PhysicsController::update()
{
   world.update();
    model.updateData();
}

void PhysicsController::reset()
{
    model.clean(world.m_dynamicsWorld);
    model.setup(world.m_dynamicsWorld);
}
void PhysicsController::drawGui(){}