/*
 * StellaAI is the legal property of its developers.
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
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
	if(rom!=""){
		setRom(rom);
	}
	else
		loadedRom = "";
}

AIRewards::~AIRewards(){
	delete script;
}

void AIRewards::setRom(string rom) {
	loadedRom = rom;
	script->loadGame(rom);
}
bool AIRewards::isRomSet() {
	return loadedRom != "";
}

void AIRewards::update(){
	if(isRomSet())
		script->call("update");
}

int AIRewards::getReward(RewardType type){
	if(!isRomSet())
		return 0;
	
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
