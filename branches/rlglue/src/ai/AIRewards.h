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
	
	void setRom(string);
	bool isRomSet();
	
	void update();
	int getReward(RewardType);
	
private:
	AIScript *script;
	OSystem *system;
	string loadedRom;
};

#endif

