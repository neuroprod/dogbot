#include "MeshDataPool.h"
#include "Mesh.h"
#include "../RobotSettings.h"
#include "cinder/ObjLoader.h"
#include <glm/gtc/constants.hpp>
using namespace ci;
using namespace ci::app;
using namespace std;


MeshDataPool::MeshDataPool() {

}
void MeshDataPool::setup()
{

	mGlsl = gl::GlslProg::create(loadAsset("shaders/mainShader.vert.glsl"), loadAsset("shaders/mainShader.frag.glsl"));

    ankle = TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/ankle.obj"))) );
}

MeshDataRef MeshDataPool::getMesh(std::string type)
{
	
	Color baseColor = Color(1, 1, 1);
	Color feetColor = Color(1,0, 0);
	Color motorColor = Color(0.8, 0.0, 0.0);

	MeshDataRef nd = MeshData::create();
	nd->type = type;
	if (type == "body") 
	{
		
		MeshRef m = Mesh::create();
		m->setup(geom::Cube().size( BOTSETTINGS()->bodyLength, 80.0f, BOTSETTINGS()->bodyWidth), baseColor, mGlsl);
		nd->meshes.push_back(m);


	/*	MeshRef motor1 = Mesh::create();
		motor1->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1, 0, 0)).origin(vec3(0, 0, 0)), vec3(-config->bodyLength/2, 0, -config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor1);

		MeshRef motor2 = Mesh::create();
		motor2->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1, 0, 0)).origin(vec3(0, 0, 0)), vec3(-config->bodyLength / 2, 0, +config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor2);


		MeshRef motor3 = Mesh::create();
		motor3->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(-1, 0, 0)).origin(vec3(0, 0, 0)), vec3(config->bodyLength / 2, 0, -config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor3);

		MeshRef motor4 = Mesh::create();
		motor4->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(-1, 0, 0)).origin(vec3(0, 0, 0)), vec3(config->bodyLength / 2, 0, +config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor4);*/


	}
	if (type == "ankle")
	{
		
		MeshRef m = Mesh::create();
		m->setup(ankle,  baseColor, mGlsl,vec3(0, 0, 0),vec3(0, glm::pi<float>()/2.f, 0));
		nd->meshes.push_back(m);

		MeshRef m2 = Mesh::create();
		m2->setup(geom::Sphere().radius(BOTSETTINGS()->footRadius), feetColor, mGlsl,vec3(0, -BOTSETTINGS()->underLegLength + BOTSETTINGS()->footRadius, 0));
		nd->meshes.push_back(m2);
	}
	/*if (type == "hip2")
	{
	
		MeshRef m = Mesh::create();
		m->setup(geom::Capsule().radius(22).length(config->upperLegLength ).center(vec3(0,-config->upperLegLength/2,0)), vec3(0, 0, 0), baseColor, mGlsl);
		nd->meshes.push_back(m);

	
		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1,0,0)).origin(vec3(-config->hipOffsetZ +20, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}*/
	if (type == "hip1_mirror")
	{
	
	
		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(0, 0, -1)).origin(vec3(config->hipOffsetX, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}
	if (type == "hip1")
	{



		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(0, 0, 1)).origin(vec3(config->hipOffsetX, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}

	return nd;
}

