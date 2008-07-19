/*
 *  AIKmeans.h
 *  stella
 *
 *  Created by Andre Cohen on 10/11/07.
 *
 */
#ifndef	AIKMEANS_H
#define AIKMEANS_H

#include <vector>
#include "AIGlobal.h"
#include "AIBase.h"
#include "AICentroid.h"
#include "AICluster.h"

using namespace std;

class AIKmeans : public AICluster {
public:
	AIKmeans(AIBase *);
	~AIKmeans();
	
	virtual void cluster();
	virtual vector<Object *> getObjects(ObjectType);
	
	void reset(bool);
	void normalize();
	void print(bool);
	
private:
	void assignPixel(int,int);
	double recenter(Centroid *);
	
	double manhattan(int,int,int,int);
	double euclid(int,int,int,int);
			
	Centroids centroid;
	
};

#endif