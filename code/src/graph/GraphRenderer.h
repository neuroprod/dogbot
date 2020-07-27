//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHRENDERER_H
#define BOT_GRAPHRENDERER_H
#include "../utils/Singleton.h"
#include "Graphable.h"

class GraphRenderer
{
public :
    GraphRenderer(){};
    void reg(Graphable * graphable);
    void draw();

    std::vector<Graphable *> graphables;
};
typedef Singleton<GraphRenderer> GraphRendererSingleton;

inline GraphRenderer *GRAPH()
{
    return GraphRendererSingleton::Instance();
}

#endif //BOT_GRAPHRENDERER_H
