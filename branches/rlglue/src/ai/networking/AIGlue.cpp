/*
 *  AIGlue.cpp
 *  stella
 *
 *  Created by Andre Cohen on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>
#include <netdb.h> 
#include <arpa/inet.h> 

#include "RL_network.h"
#include "RL_common.h"
#include "Environment_common.h"
#include "AIGlue.h"
#include "AIProtocol.h"


AIGlue::AIGlue(){
	host = "127.0.0.1";
	port = 4096;
}

AIGlue::~AIGlue(){
	rlEndEnvironment();
}

bool AIGlue::connect(){
	cerr<<"Waiting for incomming connection...\n";
	if(!(connection = rlStartEnvironment(host, port))){
		cerr<<"Error creating environment connection\n";
		return false;
	}
	return connection;
}

bool AIGlue::isConnected(){
	return connection>0;
}

void AIGlue::runEventLoop(AIBase *base){
	rlUpdateEnvironment();
}


