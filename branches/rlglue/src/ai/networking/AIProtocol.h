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
