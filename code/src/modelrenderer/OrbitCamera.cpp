#include "OrbitCamera.h"

using namespace ci;
using namespace ci::app;
using namespace std;


void OrbitCamera::setup()
{

}
void OrbitCamera::drawGui()
{
	/*ui::ScopedWindow window("camera");

	if (ui::DragFloat("fov", &fov, 1, 5, 170));
	if (ui::DragFloat("theta", &theta, 0.01, 0.001, 3.1415 / 2)) ;
	if (ui::DragFloat("phi", &phi, 0.01, 0, 3.1415*2)) ;
	if (ui::DragFloat("distance", &cameraDistance, 1)) ;
*/

}
void OrbitCamera::update(ImVec2 vMin,ImVec2 vMax)
{
    ImGuiIO& io = ImGui::GetIO();

    if(! mMouseDown)
    {
        if(io.MouseDown[0])
        {
            if(io.MousePos.x >vMin.x && io.MousePos.x <vMax.x && io.MousePos.y >vMin.y && io.MousePos.y <vMax.y &&  ImGui::IsWindowFocused() )
            {

                mMouseDown =true;
                //down;
                mouseDown(vec2(io.MousePos.x,io.MousePos.y));
            }

        }

    }
   else  if( mMouseDown && !io.MouseDown[0])
    {
        mMouseDown =false;
        mouseUp(vec2(io.MousePos.x,io.MousePos.y));
    }
    else  if( mMouseDown)
    {

        mouseDrag(vec2(io.MousePos.x,io.MousePos.y));
    }
    if(io.MouseWheel !=0)
    {
        if(io.MousePos.x >vMin.x && io.MousePos.x <vMax.x && io.MousePos.y >vMin.y && io.MousePos.y <vMax.y &&  ImGui::IsWindowFocused() )
        {
            mouseWheel(io.MouseWheel);
        }

    }


	offsetPos += ( targetPos-offsetPos) / 20.f;

	
	phi += deltaPhi;
	phi = glm::mod(phi, 3.1415f*2);
	theta += deltaTheta;

	theta = glm::clamp(theta, 0.01f, 3.1415f / 2);

	
	float x = cameraDistance * sinf(theta)*cosf(phi);
	float z = cameraDistance * sinf(theta)*sinf(phi);
	float y = cameraDistance * cosf(theta);

	mCam.lookAt(vec3(x, y , z)+ offsetPos, vec3(0, 0, 0)+ offsetPos);
	mCam.setPerspective(fov, aspect, 20, 10000);

	deltaPhi *= (1 - dampingFactor);
	deltaTheta *= (1 - dampingFactor);
	
	cameraDistance += ( targetCameraDistance- cameraDistance ) *dampingFactor;


}
void OrbitCamera::setBodyPos(ci::vec3 pos) 
{
	targetPos = pos;
	targetPos.y /= 2.f;

}
void OrbitCamera::mouseDown(vec2 pos)
{
	rotateStart =pos;
}
void  OrbitCamera::mouseDrag(vec2 pos)
{

	if (pos == rotateEnd)return;
	rotateEnd =  pos;
	
	vec2 rotateDelta = rotateEnd - rotateStart;

	deltaPhi=2 * 3.1415 * rotateDelta.x / 1024.f;
	deltaTheta=-2 * 3.1415 * rotateDelta.y / 1024.f;

	phi += deltaPhi;
	theta += deltaTheta;

	rotateStart = rotateEnd;
	
}
void OrbitCamera::mouseUp(vec2 pos)
{
	
}
void OrbitCamera::mouseWheel(float inc_)
{
	int inc =  inc_ ;
	if (inc > 0) 
	{
		targetCameraDistance*=0.9;
	}
	else 
	{
		targetCameraDistance/=0.9;
	}
	if(targetCameraDistance>4000)targetCameraDistance=4000;
}