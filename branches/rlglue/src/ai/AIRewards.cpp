/*
 *  AIRewards.cpp
 *  stella
 *
 *  Created by Andre Cohen on 7/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <ctime>
using namespace std;

#include "AIRewards.h"
#include "OSystem.hxx"
#include "Debugger.hxx"
#include "CpuDebug.hxx"
#include "AIScript.h"


AIRewards::AIRewards(OSystem *system, string rom){
	script = new AIScript(system);
	script->loadGame(rom);
}
AIRewards::~AIRewards(){
	delete script;
}

void AIRewards::update(){
	script->call("update");
}

int AIRewards::getReward(RewardType type){
	switch(type){
		case rt_Score:
			return script->call("score");
		case rt_Lives:
			return script->call("lives");
		case rt_Time:
			return script->call("time");
		case rt_Reward:
			return script->call("reward");
	};
	return 0;
}