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

#ifndef AI_GLUEENV_H
#define AI_GLUEENV_H

#include "AIBase.h"
#include "AIGlue.h"
#include "AIGlobal.h"
#include "AIRewards.h"

#define RLGACT_NOOP              0
#define RLGACT_FIRE              1
#define RLGACT_UP                2
#define RLGACT_RIGHT             3
#define RLGACT_LEFT              4
#define RLGACT_DOWN              5
#define RLGACT_UPRIGHT           6
#define RLGACT_UPLEFT            7
#define RLGACT_DOWNRIGHT         8
#define RLGACT_DOWNLEFT          9
#define RLGACT_UPFIRE            10
#define RLGACT_RIGHTFIRE         11
#define RLGACT_LEFTFIRE          12
#define RLGACT_DOWNFIRE          13
#define RLGACT_UPRIGHTFIRE       14
#define RLGACT_UPLEFTFIRE        15
#define RLGACT_DOWNRIGHTFIRE     16
#define RLGACT_DOWNLEFTFIRE      17

class AIGlue; 
class AIBase;
class AIRewards;

class AIGlueEnv 
{
  // I know, this is evil. 
  //
  // The env_* functions need access to this object and there's no
  // other way to give it to them. This would not be a problem if RLGlue
  // had a C++ base class with pure virtuals that you could just subclass
  // and override
  //

public:
  static AIGlue* aiGluePtr;
  static AIBase* aiBasePtr;
  static AIRewards* aiRewardsPtr;  

};

#endif

