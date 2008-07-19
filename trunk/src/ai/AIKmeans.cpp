/*
 *  AIKmeans.cpp
 *  stella
 *
 *  Created by Andre Cohen on 10/11/07.
 *
 */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include "AIGlobal.h"
#include "AIKmeans.h"
#include "AIBase.h"
#include "AICentroid.h"

#include <SDL/SDL_Events.h>
#include "FrameBuffer.hxx"
#include "EventHandler.hxx"
#include "Event.hxx"

#define CENTROIDS	20
#define GRAIN		5

AIKmeans::AIKmeans(AIBase *b) {
	base = b;
}


void AIKmeans::reset(bool full) {
	
	if (full) {
		while (centroid.size()) {
			delete *centroid.begin();
			centroid.erase(centroid.begin());
		}
	}
	else {
		// Save previous identified centroids
		for (size_t i=0;i<centroid.size();i++) {
			if (centroid[i]->type==Undefined){
				delete *(centroid.begin()+i);
				centroid.erase(centroid.begin()+i);
			}
			else
				centroid[i]->type = Undefined;
		}
	}
	

	// Add extra random centroids
	for (;centroid.size()<CENTROIDS;) {
		centroid.push_back(new Centroid((rand()+10)%base->frameBuffer->imageWidth()-10,(rand()+10)%base->frameBuffer->imageHeight()-10));
	}
	
}

AIKmeans::~AIKmeans(){
	while(centroid.begin()!=centroid.end()){
		delete *centroid.begin();
		centroid.erase(centroid.begin());
	}
}

void AIKmeans::cluster() {
	double d = -1;
	
	// Print previous results 
	print(true);
	reset(true);
	
	// While centroids are still repositioning 
	while (d==-1 || d>0) {
		d = 0;
		
		// Identify each pixel
		for (Uint32 y=0;y<base->frameBuffer->imageHeight();y=y+GRAIN) {
			for (Uint32 x=0;x<base->frameBuffer->imageWidth();x=x+GRAIN) {
				assignPixel(x,y);
			}
		}
		
		// Recalculate centroids
		for (size_t i=0;i<centroid.size();i++) {
			double tmp = recenter(centroid[i]);
			if (tmp>d)
				d = tmp;
		}
	}

	// Clean up data
	normalize();
}

void AIKmeans::assignPixel(int x, int y) {
	Uint32 color = base->getPixel(x,y);
	ObjectType t = Undefined;
	
	if (color==0x5fa55a||color==0xe17690)
		t = Man;
	else if (color==0x912640||color==0x787878)
		t = Wall;
	else if (color==0x6c7c00 && y>300 && y<350)
		t = Ladder;
	else if (color==0x586800)
		t = Log;
	else if (color==0xc8c8c8 && y>350 && y<400)
		t = Scorpion;
	else if (color==0x2c6a82 && y>200 && y<250)
		t = Water;
	else if (color==0x000000 && y>200 && y<250 && x>150 && x<600)
		t = Sand;
	else if (color==0x1f5100 && y>200 && y<250)
		t = Croc;
	else if (color==0x445400 && y>180 && y<200)
		t = Vine;
	
	if (t!=Undefined) {
		int c = -1;
		double d = 0;
		
		for (size_t i=0;i<centroid.size();i++) {
			double tmp = euclid(x,y,centroid[i]->center.x,centroid[i]->center.y);
			
			if ((c<0 || tmp<d) &&
			    (centroid[i]->type==Undefined || (centroid[i]->type==t && tmp<200))) {
				c = i;
				d = tmp;
			}
		}
		
		// Update selected centroid
		if (c>-1) {
			centroid[c]->addPoint(x,y);
			centroid[c]->avg.x = centroid[c]->avg.x+x;
			centroid[c]->avg.y = centroid[c]->avg.y+y;
			centroid[c]->count = centroid[c]->count+1;	
			centroid[c]->type = t;
		}
	}	
}

// Compare two centroids by location and type
bool operator != (Centroid a, Centroid b) {
	return !(a.type==b.type && a.center.x==b.center.x && a.center.y==b.center.y);
}

void AIKmeans::normalize() {
	vector<Centroid *>::iterator c = centroid.begin();
	while (c!=centroid.end()) {
		vector<Centroid *>::iterator c2 = centroid.begin();
		while (c2!=centroid.end()) {
			// Join 2 centroids together if they are the same type and around each other
			if (c!=c2 && (*c)->type == (*c2)->type && 
			   (euclid((*c)->center.x,(*c)->center.y,(*c2)->center.x,(*c2)->center.y)<10 || (*c)->type==Man)) {
				(*c)->avg.x=(*c)->avg.x+(*c2)->center.x;
				(*c)->avg.y=(*c)->avg.y+(*c2)->center.y;
				(*c)->count=(*c)->count+1;
				(*c2)->type = Undefined;
			}
			c2++;
		}
		recenter((*c));
		c++;
	}
}

// Recenters centroid given new points that have been added to it
double AIKmeans::recenter(Centroid *c) {
	if (c->count>0) {
		Point p;
		p.x = ((c->avg.x/c->count)+c->center.x)/2;
		p.y = ((c->avg.y/c->count)+c->center.y)/2;
		
		double d = fabs((p.x-c->center.x)+(p.y-c->center.y));
		
		c->center = p;
		
		c->avg.x = 0;
		c->avg.y = 0;
		c->count = 0;
		
		return d;
	}
	return -1;
}

vector<Object *> AIKmeans::getObjects(ObjectType t){
	vector<Object *> objs;
	
	for(size_t i=0;i<centroid.size();i++){
		if((t==Any || centroid[i]->type==t) && centroid[i]->type!=Undefined){
			Object *o = new Object();
			o->type=centroid[i]->type;
			o->dimension = centroid[i]->dim;
			
			objs.push_back(o);
		}
	}
	
	return objs;
}

void AIKmeans::print(bool show) {
	for (size_t i=0;i<centroid.size();i++) {
		if(centroid[i])
			centroid[i]->print(base,show,true);
	}
	cout<<"\n\n";
}

double AIKmeans::manhattan(int x1, int y1,int x2, int y2){
	return abs((x1-x2)+(y1-y2));
}

double AIKmeans::euclid(int x1, int y1, int x2, int y2){
	return sqrt(pow((x2-x1)+(y2-y1),2));
}
