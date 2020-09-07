#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "../utils/Singleton.h"


class SymbolBatches 
{
    void setup();
    void makeFloor();
    void makeHome();
    void makeCoordinateFrame();
    void makeTarget();
    void makeCOF();
    void makeSphere();
public:
    SymbolBatches() {setup();};


	ci::gl::BatchRef floorBatch;
	ci::gl::BatchRef homeBatch;
	ci::gl::BatchRef targetBatch;
	ci::gl::BatchRef coordinateFrame;
	ci::gl::BatchRef COFBatch;
    ci::gl::BatchRef sphereBatch;
};
typedef Singleton<SymbolBatches > SymbolBatchesSingleton;

inline SymbolBatches * SYMBOLBATCHES() {
    return  SymbolBatchesSingleton::Instance();
}
