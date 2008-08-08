/*
 *  AIFindScore.h
 *  stella
 *
 *  Created by Andre Cohen on 7/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef AIFINDSCORE_H
#define AIFINDSCORE_H

#include <vector>
#include <string>
#include <time.h>
#include <ctime>
using namespace std;

#include "OSystem.hxx"
#include "AIScript.h"
class AIScript;
class OSystem;


enum RewardType {rt_Score,rt_Time,rt_Lives,rt_Reward};


class AIRewards {
public:
	AIRewards(OSystem*, string);
	~AIRewards();
	
	void update();
	int getReward(RewardType);
	
private:
	AIScript *script;
	OSystem *system;
};

#endif

