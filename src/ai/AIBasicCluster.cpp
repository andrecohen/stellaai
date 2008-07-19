/*
 *  AIBasicCluster.cpp
 *  stella
 *
 *  Created by Andre Cohen on 10/23/07.
 *
 */

#include "AIBasicCluster.h"
#include "AIGlobal.h"
#include "AICluster.h"
#include "AIBase.h"

#define GRAIN	1		

AIBasicCluster::AIBasicCluster(AIBase *b) {
	base = b;
}

AIBasicCluster::~AIBasicCluster() {
	clearObjects(previous);
	clearObjects(current);
}

void AIBasicCluster::cluster() {
	Point loc;
	int color; 
	ObjectType type;
	
	// Make current state be the previous state
	if(previous.size())
		clearObjects(previous);
	if(current.size()){
		previous.resize(current.size());
		copy(current.begin(),current.end(),previous.begin());
		current.clear();
	}
	
	for(loc.y=0;loc.y<(int)base->frameBuffer->imageHeight();loc.y=loc.y+1) {	
		for(loc.x=0;loc.x<(int)base->frameBuffer->imageWidth();loc.x=loc.x+1) {
			color = base->getPixel(loc.x,loc.y);
			type = Undefined;
			
			// Identify object
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
			else if (color==0x86861d && loc.y>359)
				type = Sand;
			else if (color==0x000000 && loc.y>200 && loc.y<255 && loc.x>150 && loc.x<600)
				type = Hole;
			else if (color==0xbbbb35 && loc.y>200 && loc.y<300)
				type = Sand;
			else if (color==0x143c00 && loc.y>200 && loc.y<300)
				type = Croc;
			else if (color==0x484800 && loc.y>180 && loc.y<200)
				type = Vine;

			// If object has been identified then we can assign it to an object
			if (type!=Undefined) {
 				assignPixel(loc,type);
			}
		}
	}
	
	group();
	group();
}

void AIBasicCluster::assignPixel(Point p, ObjectType t) {
	Object *obj = NULL;
	
	//Check if there is an object that the pixel already belongs to
	for(size_t i=0;obj==NULL && i<current.size();i++) {
		if(current[i]->type==t && 
		   ((p.y-current[i]->dimension.max.y<2 && p.x>=current[i]->dimension.min.x && p.x<=current[i]->dimension.max.x) ||
			(p.x-current[i]->dimension.max.x<2 && p.y>=current[i]->dimension.min.y && p.y<=current[i]->dimension.max.y)))
		{
			obj = current[i];
		}
	}
		
	// Add pixel to object if object exists
	if(obj) {
		if(obj->dimension.max.x+1==p.x)
			obj->dimension.max.x=obj->dimension.max.x+1;
		if(obj->dimension.max.y+1==p.y)
			obj->dimension.max.y=obj->dimension.max.y+1;
	// Create new object for this pixel
	} else {
		obj = new Object();
		SetRect(obj->dimension,p.x,p.y,p.x,p.y);
		obj->type = t;
		current.push_back(obj);
	}
	
}

void AIBasicCluster::group() {
	Objects::iterator ia = current.begin();
	Objects::iterator ib;
	for(;ia!=current.end();ia++){
		ib = current.begin();
		for(;ib!=current.end();ib++){
			Object *a = *ia;
			Object *b = *ib;
			
			if(a!=b && a->type==b->type) {
				// Is B touching or overlapping object A?
				if(((b->dimension.min.x<=a->dimension.max.x+20) &&
				   (a->dimension.min.x<=b->dimension.max.x+20) &&
				   (b->dimension.min.y<=a->dimension.max.y+20) && 
				   (a->dimension.min.y<=b->dimension.max.y+20))
				   ||(a->type==Man)||(a->type==Wall)){

					// Adjust object A to include object B
					if(a->dimension.min.x>b->dimension.min.x)	a->dimension.min.x=b->dimension.min.x;
					if(a->dimension.min.y>b->dimension.min.y)	a->dimension.min.y=b->dimension.min.y;
					if(a->dimension.max.x<b->dimension.max.x)	a->dimension.max.x=b->dimension.max.x;
					if(a->dimension.max.y<b->dimension.max.y)	a->dimension.max.y=b->dimension.max.y;
					
					// We no longer need object B
					delete b;
					current.erase(ib);
				}
			}
			
		}
		if((*ia)->type==Log && RectWidth((*ia)->dimension)<10){
			delete (*ia);
			current.erase(ia);
		}
	}
}

void AIBasicCluster::clearObjects(Objects &objs) {
	// Remove all objects if any
	while(objs.size()>0){
		delete objs[0];
		objs.erase(objs.begin());
	}	
}

Objects AIBasicCluster::getObjects(ObjectType t) {
	return current;
}

vector<string> AIBasicCluster::getUpdate() {
	return getDiff(previous,current);
}