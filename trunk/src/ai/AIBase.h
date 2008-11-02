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

#include <set> 
#include <map>
#include <vector>

using namespace std;

#include "AIProtocol.h"
#include "AIRewards.h"
#include "AIGlobal.h"
#include "AIScript.h"
#include "OSystem.hxx"
#include "EventHandler.hxx"
#include "FrameBuffer.hxx"



class AIRewards;
class AIScript;
class AIProtocol;

class AIBase {
public:
	AIBase(OSystem*);
	~AIBase();
	void update();
	void commands();
	
	Matrix nextScreen();
	Matrix getRam();
	Matrix getScreen();
	Matrix getPrevScreen();
	
	int getScreenHeight();
	int getScreenWidth();
	
	void saveState();
	void loadState();
	
	void restartEmulation();

	void pressKey(SDLKey);
	void resetKeys();
	void sendKey(SDLKey,bool);
	bool getKeys();
	
	OSystem *getOSystem();
 
private:
	int getPixel(int,int);
	vector<unsigned char> compress(Matrix);

	int saveStack;
	
	OSystem *system;
	
	AIProtocol *comm;
	AIRewards *rewards;

	Matrix oldScreen;
	Matrix curScreen;
};


#endif


