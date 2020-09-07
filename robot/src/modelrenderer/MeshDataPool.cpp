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
if (mGlsl) return;
	mGlsl = gl::GlslProg::create(loadAsset("shaders/mainShader.vert.glsl"), loadAsset("shaders/mainShader.frag.glsl"));

	//meshes

    ankle = TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/ankle.obj"))) );

    bodyAl= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/bodyAlu.obj"))) );
    bodyPlas= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/bodyplastic.obj"))) );
    bodyBlack= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/bodyblack.obj"))) );
    bodyGreen= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/bodygreen.obj"))) );
    motor= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/motor.obj"))) );
    hip= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/hipAlu.obj"))) );
    knee= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/upperLegAlu.obj"))) );
    kneePlas= TriMesh::create(   ObjLoader (loadFile(getAssetPath("models/upperLegPlastic.obj"))) );
    //materials;
    rubber.color =Color(0.1, 0.1, 0.1);
    rubber.spec=0.1;
    plastic.color =Color(0.99, 0.99, 0.99);
    aluminium.color =Color(0.8, 0.8, 0.8);
    aluminiumBlack.color =Color(0.2, 0.2, 0.2);

    blue.color =Color(107.f/255.f, 193.f/255.f, 255.f/255.f);
}

MeshDataRef MeshDataPool::getMesh(std::string type)
{
	


	MeshDataRef nd = MeshData::create();
	nd->type = type;
	if (type == "body") 
	{
		
		MeshRef m = Mesh::create();
		m->setup(bodyAl, aluminium, mGlsl);
		nd->meshes.push_back(m);

        MeshRef m2 = Mesh::create();
        m2->setup(bodyPlas, plastic, mGlsl);
        nd->meshes.push_back(m2);





        MeshRef m3 = Mesh::create();
        m3->setup(bodyBlack, aluminiumBlack, mGlsl);
        nd->meshes.push_back(m3);


        MeshRef m4= Mesh::create();
        m4->setup(bodyGreen, blue, mGlsl);
        nd->meshes.push_back(m4);


		MeshRef motor1 = Mesh::create();
		motor1->setup(motor, aluminiumBlack, mGlsl, vec3(-BOTSETTINGS()->bodyLength/2, 0, -BOTSETTINGS()->bodyWidth/2),vec3(0, glm::pi<float>()/2.f, 0));
		nd->meshes.push_back(motor1);

        MeshRef motor2 = Mesh::create();
        motor2->setup(motor, aluminiumBlack, mGlsl, vec3(-BOTSETTINGS()->bodyLength/2, 0, BOTSETTINGS()->bodyWidth/2),vec3(glm::pi<float>(), glm::pi<float>()/2.f, 0));
        nd->meshes.push_back(motor2);

        MeshRef motor3 = Mesh::create();
        motor3->setup(motor, aluminiumBlack, mGlsl, vec3(BOTSETTINGS()->bodyLength/2, 0, -BOTSETTINGS()->bodyWidth/2),vec3(glm::pi<float>(), -glm::pi<float>()/2.f, 0));
        nd->meshes.push_back(motor3);

        MeshRef motor4 = Mesh::create();
        motor4->setup(motor, aluminiumBlack, mGlsl, vec3(BOTSETTINGS()->bodyLength/2, 0, BOTSETTINGS()->bodyWidth/2),vec3(0, -glm::pi<float>()/2.f, 0));
        nd->meshes.push_back(motor4);

	}
	if (type == "ankle")
	{
		
		MeshRef m = Mesh::create();
		m->setup(ankle,  aluminium, mGlsl,vec3(0, 0, 0),vec3(0, glm::pi<float>()/2.f, 0));
		nd->meshes.push_back(m);

		MeshRef m2 = Mesh::create();
		m2->setup(geom::Sphere().radius(BOTSETTINGS()->footRadius), rubber, mGlsl,vec3(0, -BOTSETTINGS()->underLegLength + BOTSETTINGS()->footRadius, 0));
		nd->meshes.push_back(m2);
	}
	if (type == "knee")
	{
	
		MeshRef m = Mesh::create();
		m->setup(knee, aluminium, mGlsl,vec3( -76,0,0),vec3(0, glm::pi<float>()/2.f, 0));
		nd->meshes.push_back(m);

        MeshRef mp = Mesh::create();
        mp->setup(kneePlas, plastic, mGlsl,vec3( -76,0,0),vec3(0, glm::pi<float>()/2.f, 0));
        nd->meshes.push_back(mp);

        MeshRef motor1 = Mesh::create();
        motor1->setup(motor, aluminiumBlack, mGlsl, vec3(-13,0,0),vec3(glm::pi<float>()/4.f,  -glm::pi<float>()/2.f,0));
        nd->meshes.push_back(motor1);



	}
	if (type == "hip_mirror")
	{
	
		MeshRef hipMesh = Mesh::create();
        hipMesh->setup(hip,  aluminium, mGlsl,vec3(0),vec3(glm::pi<float>(), 0, 0));
		nd->meshes.push_back( hipMesh);


        MeshRef motor1 = Mesh::create();
        motor1->setup(motor, aluminiumBlack, mGlsl, vec3(BOTSETTINGS()->hipOffsetX,0,-4),vec3(0,  0,glm::pi<float>()));
        nd->meshes.push_back(motor1);

	}
	if (type == "hip")
	{



		MeshRef hipMesh= Mesh::create();
        hipMesh->setup(hip,  aluminium, mGlsl);
		nd->meshes.push_back( hipMesh);

        MeshRef motor1 = Mesh::create();
        motor1->setup(motor, aluminiumBlack, mGlsl, vec3(BOTSETTINGS()->hipOffsetX,0,4),vec3(glm::pi<float>(),  0,glm::pi<float>()));
        nd->meshes.push_back(motor1);

	}

	return nd;
}

