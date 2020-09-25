//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHRENDERER_H
#define BOT_GRAPHRENDERER_H
#include "../utils/Singleton.h"
#include "Graphable.h"
#include "../gui/FBOWindow.h"
#include <list>
class GraphRenderer
{
public :
    GraphRenderer();
    void reg(Graphable * graphable);
    void draw(std::string type);
    void pulse(int i);
    void pauze();
    void play();
    bool isPauze =false;

    FBOWindow fboWindow;
    std::vector<Graphable *> graphables;
    std::list<int> pulseData;

};
typedef Singleton<GraphRenderer> GraphRendererSingleton;

inline GraphRenderer *GRAPH()
{
    return GraphRendererSingleton::Instance();
}

#endif //BOT_GRAPHRENDERER_H
