//
// Created by kris on 26.08.20.
//

#include "PhysicsController.h"

void PhysicsController::setup()
{




   world.setup();
   floor.setup();
   world.m_dynamicsWorld->addRigidBody(floor.body);


   model.setup(world.m_dynamicsWorld);



}
void PhysicsController::update()
{
   world.update();

}

void PhysicsController::reset()
{
    model.clean();
    model.setup(world.m_dynamicsWorld);
}
void PhysicsController::drawGui(){}