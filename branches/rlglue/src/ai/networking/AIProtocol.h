/*
 *  AIProtocol.h
 *  stella
 *
 *  Created by Andre Cohen on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef AI_PROTOCOL_H
#define AI_PROTOCOL_H

#include "AIBase.h"
#include "AIRewards.h"
#include "AIGlobal.h"
class AIBase;
class AIRewards;

class AIProtocol {
protected: 
  AIRewards* rewards; 

public:
  AIProtocol() { rewards = NULL; }
  virtual ~AIProtocol() {} 

  virtual void setRewards(AIRewards* rew) { rewards = rew; }

	virtual bool connect() = 0;
	virtual bool isConnected() = 0;
	virtual void runEventLoop(AIBase *) = 0;

  virtual void computeDiff(const Matrix & previous, const Matrix & current, 
                           Matrix & result); 
};

#endif