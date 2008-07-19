/*
 *  Pitfall.cpp
 *  stella
 *
 *  Created by Andre Cohen on 12/24/07.
 *
 */

#include <string>
using namespace std;

#include "AIGlobal.h"
#include "Classify.h"
#include "Pitfall.h"

Pitfall::Pitfall(){
}

ObjectType Pitfall::getType(int c, int x, int y) {
	Point p;
	SetPoint(p,x,y);
	return getType(c,p);
}


ObjectType Pitfall::getType(int color, Point loc) {
	ObjectType type = Undefined;
	if (color==0x5cba5c||color==0xe46f6f||(color==0x355f18 && loc.y>180))
		type = Man;
	else if (color==0x171a1a||color==0x8e8e8e)
		type = Wall;
	else if (color==0x86861d && loc.y>255 && loc.y<359 && loc.x>304 && loc.x<336)
		type = Ladder;
	else if (color==0x69690f)
		type = Log;
	else if (color==0xececec && loc.y>300 && loc.y<400)
		type = Scorpion;
	else if (color==0x2d6d98 && loc.y>200 && loc.y<300)
		type = Water;
	//else if (color==0x86861d && loc.y>359)
	//	type = Sand;
	else if (color==0x000000 && loc.y>200 && loc.y<255 && loc.x>150 && loc.x<600)
		type = Hole;
	//else if (color==0xbbbb35 && loc.y>200 && loc.y<300)
	//	type = Sand;
	else if (color==0x143c00 && loc.y>200 && loc.y<300)
		type = Croc;
	else if (color==0x484800 && loc.y>180 && loc.y<200)
		type = Vine;
	return type;
}

string Pitfall::toString(ObjectType type) {
	static char ObjectTypeName[][16]={"Any","Undefined","Man","Log","Wall","Ladder","Scorpion","Croc","Water","Sand","Hole","Vine"};	
	return ObjectTypeName[type];
}