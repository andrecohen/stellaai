/*
 *  AIScript.h
 *  stella
 *
 *  Created by Andre Cohen on 8/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _AISCRIPT_H_
#define _AISCRIPT_H_

#include <string>
using namespace std;
extern "C" {
#include <lua.h>
}


#include "OSystem.hxx"
class OSystem;

class AIScript {
public:
	AIScript(OSystem *);
	~AIScript();
	
	bool loadGame(string);
	int call(string);
private:
	
	lua_State *state;
};

#endif
