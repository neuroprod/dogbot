//
// Created by kris on 26.08.20.
//

#ifndef BOT_PHYSICSCONTROLLER_H
#define BOT_PHYSICSCONTROLLER_H


#include "PhysicsWorld.h"
#include "Floor.h"
#include "PhysicsModel.h"
class PhysicsController
{
public:
    PhysicsController( ){}
    void setup(ci::mat4 defaultmatrix ,std::vector<float>  defaultAngles);
    void reset();
    void update();
    void drawGui();

   PhysicsWorld world;
   Floor floor;
    PhysicsModel model;
};


#endif //BOT_PHYSICSCONTROLLER_H
