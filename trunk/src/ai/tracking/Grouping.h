/*
 *  Grouping.h
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GROUPING_H
#define GROUPING_H

#include "Scripting.h"

class Grouping : public Scripting {
public:
	Grouping(char *);
	
	bool apply(Object *, Object *);
};

#endif