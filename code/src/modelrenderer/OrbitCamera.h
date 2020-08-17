#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderImGui.h"
class OrbitCamera
{
public:
	OrbitCamera() {}
	void setup();
	void update( ImVec2 vMin,ImVec2 vMax);
	void drawGui();
	void mouseDown(ci::vec2 pos) ;
	void mouseDrag(ci::vec2 pos) ;
	void mouseUp(ci::vec2 pos);
	void mouseWheel(float inc);
	void setBodyPos(ci::vec3 pos);

    bool mMouseDown =false;

	ci::CameraPersp	mCam;

	ci::vec2 rotateStart;
	ci::vec2 rotateEnd;
	float cameraDistance = 2360;
	float targetCameraDistance = cameraDistance;
	float dampingFactor = 0.1;

	float phi = 0.891;
	float theta = 1.162;
	float fov = 30;
	
	float deltaTheta =0;
	float deltaPhi=0;
    float aspect =0.5;

	ci::vec3 targetPos =ci::vec3(0,0,0);
	ci::vec3 offsetPos = ci::vec3(0, 0, 0);
};