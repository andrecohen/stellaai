/*
 *  Object.cpp
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <math.h>

#include "Object.h"

using namespace std;

Object::Object() {
	parent = NULL;
	visited = false;
	uid = rand();
	name = "";
}

Object::Object(Object *o) {
	x = o->x;
	y = o->y;
	w = o->w;
	h = o->h;
	color = o->color;
	name = o->name;
	uid = o->uid;
	parent = NULL;
	visited = false;
}

bool Object::touches(Object *B) {
	if(B->x>=x-1 && B->maxX()<=maxX()+1 && y+1==B->y)
		return true;
	if(x>=B->x+1 && maxX()<=B->maxX()+1 && y+1==B->y)
		return true;
	if(B->x>x && B->maxX()<maxX() && B->y>y && B->maxY()<maxY())
		return true;
	return false;
}

double Object::distance(Object *B) {
	double s1 = distance(B->x,B->y);
	double s2 = distance(B->maxX(),B->y);
	if(s2<s1)	s1 = s2;
	s2 = distance(B->x,B->maxY());
	if(s2<s1)	s1 = s2;
	s2 = distance(B->maxX(),B->maxY());
	if(s2<s1)	s1 = s2;
	return s1;
}

double Object::distance(int px, int py) {
	double d1 = sqrt(pow(x-px,2)+pow(y-py,2));
	double d2 = sqrt(pow(maxX()-px,2)+pow(y-py,2));
	if(d2<d1)	d1 = d2;
	d2 = sqrt(pow(x-px,2)+pow(maxY()-py,2));
	if(d2<d1)	d1 = d2;
	d2 = sqrt(pow(maxX()-px,2)+pow(maxY()-py,2));
	if(d2<d1)	d1 = d2;
	return d1;
}

Object *Object::buildFromLink() {
	Object *final = new Object(this);
	
	for(int i=0; i<link.size(); i++) {
		if(!link[i]->visited) {
			Object *tmp = link[i]->buildFromLink();		
			
			final->group(tmp);

			delete tmp;
			link[i]->visited = true;
		}
	}
	
	visited = true;
	return final;
}

void Object::group(Object *B) {
	if(B->x<x) {
		w = w + (x - B->x);
		x = B->x;
	}
	if(B->y<y) {
		h = h + (y - B->y);
		y = B->y;
	}
	if(B->maxX()>maxX())	w = B->maxX() - x;
	if(B->maxY()>maxY())	h = B->maxY() - y;	
}

void Object::describe() {
	cout<<name<<": ("<<x<<","<<y<<"):"<<w<<"x"<<h<<"\t"<<hex<<color<<"\tLinks: "<<dec<<link.size()<<endl;
}