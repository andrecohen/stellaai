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
class AIBase;

class AIProtocol {

public:
  virtual ~AIProtocol() {} 

	virtual bool connect() = 0;
	virtual bool isConnected() = 0;
	virtual void runEventLoop(AIBase *) = 0;
};

#endif
