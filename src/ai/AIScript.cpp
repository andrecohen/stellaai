/*
 *  AIScript.cpp
 *  stella
 *
 *  Created by Andre Cohen on 8/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
using namespace std;

#include "AIScript.h"
#include "OSystem.hxx"
#include "Debugger.hxx"

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

OSystem *osystem = NULL;

int getArgument(lua_State *s,string function){
	int argc = lua_gettop(s);
	if(argc==0){
		cerr<<"[Script] "<<function<<" needs 1 argument\n";
		return -1;
	}
	return lua_tonumber(s, 1);
}

int log(lua_State *s){
	int args = lua_gettop(s);
	for(int n=1;n<=args;n++)
		cerr<<"[Script] "<<lua_tostring(s, n)<<endl;
	return args>0;
}

int getRam(lua_State *s){
	Debugger *db = &osystem->debugger();
	
	int addr = getArgument(s,"getRam");

	if(!db){
		lua_pushnumber(s,0);
		return 0;
	}
	lua_pushnumber(s,db->peek(addr));
	return 1;
}

int toHex(lua_State *s){
	int val = getArgument(s,"toHex");
	lua_pushnumber(s,atoi(Debugger::to_hex_8(val)));
	return 1;
}

int toBin(lua_State *s){
	int val = getArgument(s,"toBin");
	lua_pushnumber(s,atoi(Debugger::to_bin_16(val)));
	return 1;
}

AIScript::AIScript(OSystem *sys){
	state = lua_open();
	
	luaopen_io(state);
	luaopen_base(state);
	luaopen_table(state);
	luaopen_string(state);
	luaopen_loadlib(state);
	
	lua_register(state, "getRam", getRam);
	lua_register(state, "log", log);
	lua_register(state, "toHex", toHex);
	lua_register(state, "toBin", toHex);
	
	osystem = sys;
}

AIScript::~AIScript(){
	lua_close(state);
}

bool AIScript::loadGame(string rom){
	// Load script file
	string path = "rewards/"+rom+".lua";
	int result = luaL_loadfile(state,path.c_str());
	
	if(result!=0){
		cerr<<"[Script] This game does not have a script associated with it!\n";
	}else{
		cerr<<"Script "<<path<<" loaded\n";
	}	
	
	// Read/execute script file
	lua_pcall(state,0,0,0);
	
	return result==0;
}

int AIScript::call(string function){
	// Set the function we want to call
	lua_getglobal(state,function.c_str());
	
	// Make the call with no parameters but expecting one value to be returned
	int result = lua_pcall(state, 0, 1, 0);
	if(result!=0){
		cerr<<"[Script] Function "<<function<<" not defined!\n";
		cerr<<lua_tostring(state,-1)<<endl;
		return -1;
	}
	
	// Get return value
	result = lua_tonumber(state, -1);
	lua_pop(state,1);
	return result;
	
}

