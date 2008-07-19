/*
 *  FastCluster.h
 *  stella
 *
 *  Created by Andre Cohen on 12/24/07.
 *
 */

#ifndef _FAST_CLUSTER_H_
#define _FAST_CLUSTER_H_

#include <vector>
using namespace std;

#include "AICluster.h"

class FastCluster : public AICluster {
public:
	FastCluster(AIBase *);
	~FastCluster();
	
	virtual void cluster();
	virtual Objects getObjects(ObjectType);
	virtual vector<string> getUpdate();
private:
	void groupObjects();
	Object *traceObject(ObjectType,Point);
	Object *expandObject(Object*, int, int);
	bool inObject(ObjectType,Point);
	Objects objects[2];
};

#endif