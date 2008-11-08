/*
 *  Tracking.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TRACKING_H
#define TRACKING_H

#include <set>

#include "Object.h"
#include "Matching.h"

class Tracking {
public:
	Tracking(Objects, Objects);
	
	Objects update();
	
private:
	set<string> objectTypes();
	Objects trackObject(string);
	
	Matching *matcher;
	
	Objects t1, t2;
	
};

#endif