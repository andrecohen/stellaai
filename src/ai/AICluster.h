/*
 *  AICluster.h
 *  stella
 *
 *  Created by Andre Cohen on 10/22/07.
 *
 */

#ifndef _AICLUSTER_H_
#define _AICLUSTER_H_

#include "AIGlobal.h"
#include <vector>

using namespace std;

class AICluster {
public:
		AICluster() {base=NULL;}
		AICluster(AIBase *);
		virtual ~AICluster(){}
		virtual void cluster() = 0;
		virtual Objects getObjects(ObjectType) = 0;
		virtual void print();

		virtual vector<string> getUpdate() = 0;
		vector<string> getDiff(Objects &, Objects &);
		
protected:
		void debug(Object *);
		
		AIBase *base;
};

#endif
