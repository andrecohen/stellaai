/*
 *  AIBasicCluster.h
 *  stella
 *
 *  Created by Andre Cohen on 10/23/07.
 *
 */

#ifndef _AIBASICCLUSTER_H_
#define _AIBASICCLUSTER_H_

#include <string>
#include <vector>

using namespace std;

#include "AIGlobal.h"
#include "AICluster.h"

class AIBasicCluster : public AICluster {
public:
	AIBasicCluster(AIBase *);
	~AIBasicCluster();
	
	virtual void cluster();
	virtual vector<string> getUpdate();
	
	virtual Objects getObjects(ObjectType);
	Objects getPreviousFrame(){return previous;}
	Objects getCurrentFrame(){return current;}
private:
	void clearObjects(Objects &);
	void assignPixel(Point,ObjectType);
	void group();
	
	Objects previous, current;
};


#endif