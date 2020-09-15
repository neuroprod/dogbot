


#include "cinder/CinderImGui.h"

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "cinder/gl/gl.h"
#include "cinder/Serial.h"
using namespace ci;
using namespace ci::app;
using namespace std;
class RemoteApp : public App
{
public:
    void setup() override;

    void update() override;

    void draw() override;
    SerialRef	mSerial;
};

void RemoteApp::setup()
{
    setFrameRate(60);
    gl::enableVerticalSync(false);

    setWindowSize(500, 500);
//sudo usermod -a -G dialout $USER
//reboot
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;

    try {

        mSerial = Serial::create(Serial::Device("ttyACM0"), 115200 );
    }
    catch( SerialExc &exc ) {
      console()<< "coult not initialize the serial device"<<endl;

    }
}


void RemoteApp::update()
{
    if(mSerial)
    {
        std::string mLastString= mSerial->readStringUntil('\n',80);
        if(mLastString.length()>1){

            console() << "last string: " << mLastString ;
        }

    }

}

void RemoteApp::draw()
{


}


CINDER_APP(RemoteApp, RendererGl, [](App::Settings *settings)
{


}
)