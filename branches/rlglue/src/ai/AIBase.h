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

#ifndef AIBASE_H
#define AIBASE_H

#include "AIComm.h"
#include "AIRewards.h"
#include "OSystem.hxx"
#include "EventHandler.hxx"
#include "FrameBuffer.hxx"

class AIRewards;

class AIBase {
public:
	AIBase(OSystem*);
	~AIBase();
	void update();
	void commands();
	
	void sendFullScreen();
	void sendDiffScreen();
	
	void sendRam();
	
	void saveState();
	void loadState();
	
	void pressKey(SDLKey);
	void resetKeys();
	void sendKey(SDLKey,bool);
	bool getKeys();
	
	int getPixel(int,int);
	
	OSystem *getOSystem();
	
private:
	Matrix getScreen();
	int getScreenHeight();
	int getScreenWidth();
	int	saveStack;
	
	OSystem *system;
	
	AIComm *comm;
	AIRewards *rewards;
	Matrix screen;
};

#endif


