/*
 *  AICentroid.h
 *  stella
 *
 *  Created by Andre Cohen on 10/18/07.
 *
 */

#ifndef AICENTROID_H
#define AICENTROID_H

#include <vector>
#include "AIBase.h"
#include "AIKmeans.h"
#include "AIGlobal.h"

using namespace std;

class Centroid{
public:
	Centroid(int,int);
	double recenter();
	void print(AIBase *,bool,bool);
	void addPoint(int,int);
	
	int getWidth();
	int getHeight();
	
	Point center;
	Point avg;
	Rect dim;
	
	int count;
	ObjectType type;
};

#endif