/*
 *  Grouping.cpp
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/1/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Grouping.h"

Grouping::Grouping(char *filename) {
	loadFile(filename);
}


bool Grouping::apply(Object *A, Object *B) {
	Objects array;
	array.push_back(A);
	array.push_back(B);
	setObjects(array);
	
	call("group");
	passInt(0);
	passInt(1);
	return i_executeCall();
}