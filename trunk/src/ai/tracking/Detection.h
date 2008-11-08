/*
 *  Detection.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DETECTION_H
#define DETECTION_H

#include <SDL/SDL.h>

#include "Scripting.h"
#include "Object.h"

class Detection {
public:
	Detection(SDL_Surface *, char *);
	
	void groupPixels();
	
	int groupLines();
	
	Objects getObjects() { return objects; }

private:
	Objects updateLine(int, int, int, int);
	void linkLines(int, int);
	
	vector<int> aroundObject(Object *, int);
	
	SDL_Surface *frame;
	Objects objects;
};


#endif