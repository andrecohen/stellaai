/*
 * StellaAI is the legal property of its developers.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <string>
#include <iostream>
#include <netdb.h> 
#include <arpa/inet.h> 

#include <rlglue/Environment_common.h>

#include "RLglue_codec.h"
#include "AIGlue.h"
#include "AIGlueEnv.h"
#include "AIProtocol.h"

using namespace std; 

AIGlue::AIGlue(){
	host = (char*)"127.0.0.1";
	port = 4096;
  AIGlueEnv::aiGluePtr = this; 
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
  //cout << "Running Event loop.." << endl; 
  
  AIGlueEnv::aiBasePtr = base; 
  AIGlueEnv::aiRewardsPtr = rewards;

  //cout << "Reward = " << r << endl; 
		
	rlUpdateEnvironment();
}


