//
// Created by kris on 22.07.20.
//

#ifndef BOT_GRAPHABLE_H
#define BOT_GRAPHABLE_H


class Graphable
{
public:
    Graphable(){}
    prepGraph(std::string name, int length, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names);
    void addData(std::vector<float> data);
    void gDraw();
    std::string gName;
    std::vector<float> gScale;
    std::vector<ci::Color> gColors;
    std::vector<std::string> gNames;
    bool gVisible =false;
};


#endif //BOT_GRAPHABLE_H
