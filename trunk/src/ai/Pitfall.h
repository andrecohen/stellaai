/*
 *  Pitfall.h
 *  stella
 *
 *  Created by Andre Cohen on 12/24/07.
 *
 */

#ifndef _PITFALL_H_
#define _PITFALL_H_

#include "Classify.h"

class Pitfall : public Classify {
public:
	Pitfall();
	
	virtual ObjectType getType(int,int,int);
	virtual ObjectType getType(int, Point);
	virtual string toString(ObjectType);
private:
};

#endif