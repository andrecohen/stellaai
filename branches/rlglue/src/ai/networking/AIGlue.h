/*
 *  AIGlue.h
 *  stella
 *
 *  Created by Andre Cohen on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef AI_GLUE_H
#define AI_GLUE_H

#include "AIBase.h"

class AIGlue : public AIProtocol {
public:
	AIGlue();
	~AIGlue();
	
	virtual bool connect();
	virtual bool isConnected();
	virtual void runEventLoop(AIBase *);
	
private:
	char *host;
	int port;
	int connection;
};

#endif
