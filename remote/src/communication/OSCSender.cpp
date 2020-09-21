//
// Created by kris on 15.09.20.
//

#include "OSCSender.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void OSCSender::setup()
{
    // For a description of the below setup, take a look at SimpleReceiver. The only difference
    // is the usage of the atomic_bool around the connection map.
    try {
        mSender.bind();
    }
    catch ( const osc::Exception &ex ) {
        console( )<<"Error binding: " << ex.what() << " val: " << ex.value() <<endl;
       return;
    }


    mIsConnected = true;


    mThread = std::thread( std::bind(
            []( std::shared_ptr<asio::io_service> &service ){
                service->run();
            }, mIoService ));
}

void OSCSender::send(osc::Message &msg )
{
    if(!mIsConnected)return;
    mSender.send( msg, std::bind( &OSCSender::onSendError,
                                  this, std::placeholders::_1 ) );


}
void OSCSender::onSendError( asio::error_code error )
{
    if( error ) {
        console()<< "Error sending: " << error.message() << " val: " << error.value() <<endl;
        // If you determine that this error is fatal, make sure to flip mIsConnected. It's
        // possible that the error isn't fatal.
        mIsConnected = false;
        try{

            mSender.close();
        }
        catch( const osc::Exception &ex ) {
            console()<<  "Cleaning up socket: val -" << ex.value()<<endl;
        }

    }
}