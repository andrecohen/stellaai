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

#include <time.h>
#include <ctime>
using namespace std;

#include "OSystem.hxx"
class OSystem;


enum RewardType {RewardScore,RewardTime};

class RewardEntry{
public:
	RewardType type;
	vector<int> locations;
};

class RewardGame {
public:
	string filename;
	vector<RewardEntry> entries;
};

class AIRewards {
public:
	AIRewards(OSystem*);
	~AIRewards();
	
	void loadData();
	
	int getReward(string,RewardType);
	
private:
	int getReward(RewardType);
	
	vector<RewardGame *> games;
	RewardGame *currentGame;
	
	OSystem *system;
};

#endif

