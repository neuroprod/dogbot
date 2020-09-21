//
// Created by kris on 15.09.20.
//

#include "OSCReceiver.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void OSCReceiver::setup()
{
    mReceiver.setListener( "/command",
                           [&]( const osc::Message &msg ){
                               std::lock_guard<std::mutex> lock( mMutex );
                               int type = msg[0].int32();
                               int command = msg[1].int32();
                               console()<<"reseive command:"<< type <<" " <<command<<endl;

                           });

    mReceiver.setListener( "/joystick",
                           [&]( const osc::Message &msg ){
                               std::lock_guard<std::mutex> lock( mMutex );
                               console()<<"j"<<endl;

                           });

    try {
        mReceiver.bind();
    }
    catch( const osc::Exception &ex ) {
        console()<< "Error binding: " << ex.what() << " val: " << ex.value() <<endl;
        return;
    }


    mReceiver.listen(
	[]( asio::error_code error, protocol::endpoint endpoint ) -> bool {
		if( error ) {
            console()<< "Error Listening: " << error.message() << " val: "
					 << error.value() << " endpoint: " << endpoint <<endl;
			return false;
		}
		else
			return true;
	});


    // Now that everything is setup, run the io_service on the other thread.
    mThread = std::thread( std::bind(
            []( std::shared_ptr<asio::io_service> &service ){
                service->run();
            }, mIoService ));

}