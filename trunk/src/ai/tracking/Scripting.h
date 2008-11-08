/*
 *  Scripting.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef SCRIPTING_H
#define SCRIPTING_H

#include <lua.h>
#include <string>

#include "Object.h"

using namespace std;

class Scripting { 
public:
	Scripting(char *);
	Scripting();
	~Scripting();
	
	void setObjects(Objects);
	
	bool loadFile(char *);
	
	void call(char *);
	void passInt(int);
	int i_executeCall();
	string s_executeCall();
	
private:
	void init();
	
	int passed;
	
	lua_State *state;
};

#endif