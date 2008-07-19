/*
 *  Classify.h
 *  stella
 *
 *  Created by Andre Cohen on 12/24/07.
 *
 */
#ifndef _CLASSIFY_H_
#define _CLASSIFY_H_

#include <string>
using namespace std;

#include "AIGlobal.h"

class Classify {
public:
	// Gets type of object based on color and location
	virtual ObjectType getType(int,int,int) = 0;
	// Gets type of object based on color and location
	virtual ObjectType getType(int, Point) = 0;
	// Returns name of object based on type
	virtual string toString(ObjectType) = 0;
};

#endif