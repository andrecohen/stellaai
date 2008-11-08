/*
 *  Scripting.cpp
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>
#include <lua.hpp>

#include "Scripting.h"

using namespace std;

static Objects objects;

int objectDistance(lua_State *state) {
	int a = luaL_checkint(state,1);
	int b = luaL_checkint(state,2);
	
	lua_pushnumber(state, objects[a]->distance(objects[b]));

	return 1;
}

int objectInfo(lua_State *state) {
	int id = luaL_checkint(state,1);
	const char *parameter = luaL_checkstring(state,2);
	
	if(strcmp(parameter, "X")==0)
		lua_pushnumber(state, objects[id]->x);
	else if(strcmp(parameter, "Y")==0)
		lua_pushnumber(state, objects[id]->y);
	else if(strcmp(parameter, "W")==0)
		lua_pushnumber(state, objects[id]->w);
	else if(strcmp(parameter, "H")==0)
		lua_pushnumber(state, objects[id]->h);
	else if(strcmp(parameter, "maxX")==0)
		lua_pushnumber(state, objects[id]->maxX());
	else if(strcmp(parameter, "maxY")==0)
		lua_pushnumber(state, objects[id]->maxY());
	else if(strcmp(parameter, "color")==0) 
		lua_pushnumber(state, objects[id]->color & 0x00ffffff);
	else if(strcmp(parameter, "name")==0)
		lua_pushstring(state, objects[id]->name.c_str());
	else if(strcmp(parameter, "describe")==0){
		objects[id]->describe();
		return 0;
	}
	else
		return 0;
	
	return 1;
}

int objectSetName(lua_State *state) {
	int id = luaL_checkint(state,1);
	string name = luaL_checkstring(state,2);
	
	objects[id]->name = name;
	
	return 0;
}

int objectInside(lua_State *state) {
	int id = luaL_checkint(state,1);
	int x = luaL_checkint(state,2);
	int y = luaL_checkint(state,3);
	int mx = luaL_checkint(state,4);
	int my = luaL_checkint(state,5);
	
	Object *obj = objects[id];
	
	lua_pushnumber(state, (obj->x>=x && obj->y>=y && obj->maxX()<=mx && obj->maxY()<=my)==true);

	return 1;
}

Scripting::Scripting() {
	init();
}

Scripting::Scripting(char *filename) {
	init();
	if(filename)
		loadFile(filename);
}

Scripting::~Scripting() {
	lua_close(state);
}

void Scripting::init() {
	state = luaL_newstate();
	
	luaopen_base(state);
	luaopen_string(state);
	
	lua_register(state, "objectInfo", objectInfo);
	lua_register(state, "objectDistance", objectDistance);
	lua_register(state, "objectInside", objectInside);
	lua_register(state, "objectSetName", objectSetName);
}

bool Scripting::loadFile(char *filename) {
	if(luaL_loadfile(state, filename)!=0){
		cout<<lua_error(state)<<endl;
		return 0;
	}
	
	if(lua_pcall(state, 0, 0, 0)!=0) {
		cout<<lua_error(state)<<endl;
		return 0;
	}
	
	return 1;
}

void Scripting::call(char *function) {
	lua_getglobal(state, function);
	passed = 0;
}

void Scripting::passInt(int val) {
	lua_pushnumber(state, val);
	passed++;
}

int Scripting::i_executeCall() {
	if(lua_pcall(state, passed, 1, 0)!=0)
		cout<<lua_error(state);

	int r = lua_tonumber(state, -1); 
	return r;
}

string Scripting::s_executeCall() {
	if(lua_pcall(state, passed, 1, 0)!=0)
		cout<<lua_error(state);
	
	string r = lua_tostring(state, -1); 
	return r;
}

void Scripting::setObjects(Objects objs) {
	objects = objs;
}
