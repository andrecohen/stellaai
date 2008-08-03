/*
 *  AIGlueEnv.h
 *  stella
 *
 *  Created by Andre Cohen on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef AI_GLUEENV_H
#define AI_GLUEENV_H

#include "AIBase.h"
#include "AIGlue.h"
#include "AIGlobal.h"

#define RLGACT_UP                0
#define RLGACT_RIGHT             1
#define RLGACT_LEFT              2
#define RLGACT_DOWN              3
#define RLGACT_UPRIGHT           4
#define RLGACT_UPLEFT            5
#define RLGACT_DOWNRIGHT         6
#define RLGACT_DOWNLEFT          7
#define RLGACT_UPFIRE            8
#define RLGACT_RIGHTFIRE         9
#define RLGACT_LEFTFIRE          10
#define RLGACT_DOWNFIRE          11
#define RLGACT_UPRIGHTFIRE       12
#define RLGACT_UPLEFTFIRE        13
#define RLGACT_DOWNRIGHTFIRE     14
#define RLGACT_DOWNLEFTFIRE      15

class AIGlue; 
class AIBase;

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
  static AIGlue * aiGluePtr;
  static AIBase * aiBasePtr;

};

#endif

