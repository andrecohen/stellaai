/*
 *  Object.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
using namespace std;

class Object {
public:
	Object();
	Object(Object *);
	
	int maxX() { return x+w; }
	int maxY() { return y+h; }
	
	bool touches(Object *);
	double distance(Object *);
	double distance(int, int);
	void group(Object *);
	
	Object *buildFromLink();
	void describe();
	
	int x, y, w, h;
	unsigned int color;
	string name;
	int uid;
	
	vector<Object *> link;
	Object *parent;
	bool visited;
};

typedef vector< Object *> Objects;
typedef vector< Objects > Lines;

#endif