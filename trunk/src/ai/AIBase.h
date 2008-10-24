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

#include "AIProtocol.h"
#include "AIRewards.h"
#include "AIGlobal.h"
#include "AIPattern.h"
#include "AIScript.h"
#include "OSystem.hxx"
#include "EventHandler.hxx"
#include "FrameBuffer.hxx"

#define  MIN(a,b)            ((a) < (b) ? (a) : (b))

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

	void pressKey(SDLKey);
	void resetKeys();
	void sendKey(SDLKey,bool);
	bool getKeys();
	
	OSystem *getOSystem();
 
private:
	int getPixel(int,int);

	int	saveStack;
  int ticks; 
  int maxColorsPerScreen; 
	
	OSystem *system;
	
	AIProtocol *comm;
	AIRewards *rewards;

	Matrix oldScreen;
	Matrix curScreen;

  /* 
   * 
   * The stuff below is just used for collecting stats needed
   * by the UofA researchers. 
   *
   * It will soon be moved to the RL-Glue agents. 
   *
   */
  
  void init_stats(); 
  void update_stats(); 
  
  void updateUniqueTriplets(); 
  void updateUniqueCrossTriplets(); 
  void updateUniquePatterns(int rows, int cols); 
  int getNumberColors(); 
  void pixelStats(int & min, int & max, double & avg); 
	
  std::set<ptriplet> uniqueTriplets; 
  //std::set<pcrosstriplet> uniqueCrossTriplets;
  //ct2boolmap uniqueCrossTriplets; 
  std::set< vector<int> > uniquePatterns;   
  std::map<int,int> color2indexmap; 
  map< pair<int,int> , bool > **** colstatsarr;
  int color_index; 

};


#endif


