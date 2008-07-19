/*
 *  FastCluster.cpp
 *  stella
 *
 *  Created by Andre Cohen on 12/24/07.
 *
 */
#include <vector>
#include <math.h>
using namespace std;

#include "AIBase.h"
#include "AIGlobal.h"
#include "AICluster.h"
#include "Classify.h"
#include "Pitfall.h"
#include "FastCluster.h"

#define PREV 0
#define CURR 1

FastCluster::FastCluster(AIBase *b) {
	base = b;
}

FastCluster::~FastCluster() {
	for(Objects::iterator object=objects[CURR].begin();object!=objects[CURR].end();object++)
		delete *object;
	for(Objects::iterator object=objects[PREV].begin();object!=objects[PREV].end();object++)
		delete *object;
}

void FastCluster::cluster() {
	Point loc;
	Pitfall translate;
	
	for(Objects::iterator object=objects[PREV].begin();object!=objects[PREV].end();object++)
		delete *object;
	objects[PREV].clear();
	objects[PREV] = objects[CURR];
	objects[CURR].clear();
	
	for(loc.y=0;loc.y<(int)base->frameBuffer->imageHeight();loc.y=loc.y+5) {
		for(loc.x=0;loc.x<(int)base->frameBuffer->imageWidth();loc.x=loc.x+5) {
			// Get object type
			ObjectType type = translate.getType(base->getPixel(loc.x,loc.y),loc.x,loc.y);
			
			// Check if object has been found already
			if(!inObject(type,loc) && type!=Undefined && type!=Any){
				Point start = loc;
				bool back = true;
				
				// Backtrack left
				while(start.x>(int)base->frameBuffer->imageWidth() && back){
					start.x--;
					if(type!=translate.getType(base->getPixel(start.x,start.y),start)){
						back = false;
						start.x++;
					}
				}
				
				// Trace object
				Object *object = traceObject(type,start);
				
				// Add object traced
				objects[CURR].push_back(object);
			}
		}
	}
	
	groupObjects();
	
}

bool FastCluster::inObject(ObjectType type, Point loc){
	for(Objects::iterator object=objects[CURR].begin();object!=objects[CURR].end();object++){
		if(loc.x<=(*object)->dimension.max.x && loc.x>=(*object)->dimension.min.x && loc.y<=(*object)->dimension.max.y && loc.y>=(*object)->dimension.min.y)
			if((*object)->type == type)
				return true;
	}
	return false;
}

Object *FastCluster::traceObject(ObjectType type, Point loc) {
	Pitfall translate;
	Object *object = new Object();
	object->type=type;
	SetRect(object->dimension,loc.x,loc.y,loc.x,loc.y);
	bool cont = true;

	for(int radius=1;cont;radius++) {
		cont = false;
		//Top
		for(int d=loc.x-radius;d<loc.x+radius;d++){
			if(type==translate.getType(base->getPixel(d,loc.y-radius),d,loc.y-radius)){
				cont = true;
				object = expandObject(object,d,loc.y-radius);
			}
		}
		//Bottom
		for(int d=loc.x+radius;d>loc.x-radius;d--){
			if(type==translate.getType(base->getPixel(d,loc.y+radius),d,loc.y+radius)){
				cont = true;
				expandObject(object,d,loc.y+radius);
			}
		}
		//Right
		for(int d=loc.y-radius;d<loc.y+radius;d++){
			if(type==translate.getType(base->getPixel(loc.x+radius,d),loc.x+radius,d)){
				cont = true;
				object = expandObject(object,loc.x+radius,d);
			}
		}
		//Left
		for(int d=loc.y+radius;d>loc.y-radius;d--){
			if(type==translate.getType(base->getPixel(loc.x-radius,d),loc.x-radius,d)){
				cont = true;
				object = expandObject(object,loc.x-radius,d);
			}
		}
	}
	
	
	return object;
}

void FastCluster::groupObjects() {
	for(Objects::iterator a=objects[CURR].begin();a!=objects[CURR].end();a++) {
		Objects::iterator b = objects[CURR].begin();
		while(b<objects[CURR].end()) {
			Object *objA = (*a);
			Object *objB = (*b);
			if(objA!=objB && objA->type==objB->type && RectDistance(objA->dimension,objB->dimension)<50) {
				expandObject(objA,objB->dimension.min.x,objB->dimension.min.y);
				expandObject(objA,objB->dimension.max.x,objB->dimension.max.y);
				delete objB;
				b = objects[CURR].erase(b);
			}else{
				b++;
			}
		}
	}
}

Object *FastCluster::expandObject(Object *object, int x, int y) {
	if(object->dimension.min.x>x)		object->dimension.min.x=x;
	else if(object->dimension.max.x<x)	object->dimension.max.x=x;
	if(object->dimension.min.y>y)		object->dimension.min.y=y;
	else if(object->dimension.max.y<y)	object->dimension.max.y=y;
	return object;
}

Objects FastCluster::getObjects(ObjectType t) {
	return objects[CURR];
}

vector<string> FastCluster::getUpdate() {
	return getDiff(objects[PREV],objects[CURR]);
}