/*
 *  Matching.cpp
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <string>

#include "Matching.h"

using namespace std;

Matching::Matching(char *filename) {
	loadFile(filename);
}


double Matching::match(Object *A, Object *B) {
	Objects array;
	array.push_back(A);
	array.push_back(B);
	setObjects(array);
	
	call("match");
	passInt(0);
	passInt(1);
	return i_executeCall();
}