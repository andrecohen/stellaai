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
static bool printed_noscript_error = false; 

int getArgument(lua_State *s,string function){
	int argc = lua_gettop(s);
	if(argc==0){
		cerr<<"[Script] "<<function<<" needs 1 argument\n";
		return -1;
	}
	return (int)lua_tonumber(s, 1);
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

int getBit(lua_State *s){
	int val = lua_tonumber(s, 1);
	int bit = lua_tonumber(s, 2);
	lua_pushnumber(s, (val & (0x0001<<bit))>>bit);
	return 1;
}

int restartEmulation(lua_State *s){
	osystem->deleteConsole();
	osystem->createConsole();
	return 0;
}


AIScript::AIScript(OSystem *sys){
	state = lua_open();

	cout << "Initializing LUA" << endl; 
	
	lua_register(state, "getRam", getRam);
	lua_register(state, "log", log);
	lua_register(state, "toHex", toHex);
	lua_register(state, "toBin", toHex);
	lua_register(state, "getBit", getBit);
	lua_register(state, "restartEmulation", restartEmulation);

	
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
    if (!printed_noscript_error) 
    {
  		cerr<<"[Script] This game does not have a script associated with it!\n";
      printed_noscript_error = true; 
    }

		return false;
	}else{
		cerr<<"Script "<<path<<" loaded\n";
	}	
	
	// Read/execute script file
	lua_pcall(state,0,0,0);
	
	return true;
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
	result = (int)lua_tonumber(state, -1);
	lua_pop(state,1);
	return result;
	
}

