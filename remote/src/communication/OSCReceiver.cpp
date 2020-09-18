//
// Created by kris on 15.09.20.
//

#include "OSCReceiver.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void OSCReceiver::setup()
{
    mReceiver.setListener( "/mousemove/1",
                           [&]( const osc::Message &msg ){
                               int a = msg[0].int32();
                               int b = msg[1].int32();
                               console()<<a<< " "<<b<<endl;
                           });

    try {
        // Bind the receiver to the endpoint. This function may throw.
        mReceiver.bind();
    }
    catch( const osc::Exception &ex ) {
       console()<<"Error binding: " << ex.what() << " val: " << ex.value() <<std::endl;

    }


    // UDP opens the socket and "listens" accepting any message from any endpoint. The listen
	// function takes an error handler for the underlying socket. Any errors that would
	// call this function are because of problems with the socket or with the remote message.
	mReceiver.listen(
	[]( asio::error_code error, protocol::endpoint endpoint ) -> bool {
		if( error ) {
            console()<< "OSCError Listening: " << error.message() << " val: " << error.value() << " endpoint: " << endpoint <<std::endl;
			return false;
		}
		else
			return true;
	});

}