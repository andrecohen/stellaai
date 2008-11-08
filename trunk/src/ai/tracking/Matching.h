/*
 *  Matching.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MATCHING_H
#define MATCHING_H

#include "Scripting.h"

class Matching : public Scripting {
public:
	Matching(char *);
	
	double match(Object *, Object *);
	
private:
	
};


#endif