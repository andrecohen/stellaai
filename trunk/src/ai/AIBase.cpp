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

#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <ctime>
#include <math.h>
#include <SDL/SDL_events.h>
using namespace std;

#include "AIGlobal.h"
#include "AIBase.h"
#include "AIRewards.h"
#include "AIPlainText.h"
#include "AIGlue.h"
#include "AISettings.h"
#include "AIScript.h"

#include "OSystem.hxx"
#include "FrameBuffer.hxx"
#include "EventHandler.hxx"
#include "Event.hxx"
#include "Debugger.hxx"
#include "PropsSet.hxx"

// Use NONE when you want to use Stella directly 
#define PROTOCOL_NONE           0
#define PROTOCOL_PLAINTEXT	    1
#define	PROTOCOL_RLGLUE         2

static int enabled_protocol = AISettings::getInstance()->get_int_setting("enabled_protocol"); 
static bool enable_stats = false;

AIBase::AIBase(OSystem *system){

	comm = NULL; 

  if (enable_stats) init_stats(); 
	
	// Are we talking doing any sort of AI
	try{
		if (enabled_protocol == PROTOCOL_PLAINTEXT)
			comm = new AIPlainText();
		else if (enabled_protocol == PROTOCOL_RLGLUE)
			comm = new AIGlue();
		
		if (comm)
			comm->connect();
	}catch(exception e){
		cerr<<"No connection found..."<<endl;
		comm = NULL;
	}
	
	rewards = new AIRewards(system,"");
	
	this->system = system;
	saveStack = 0;
	
	if (comm)
		comm->setRewards(rewards); 
}

AIBase::~AIBase(){
	if(comm)		
		delete comm;
	if(rewards)
		delete rewards;
}

// Called at every frame
void AIBase::update(){
	
	if(rewards->isRomSet()==false && system->romFile()!=""){
		string fullPath = system->romFile();
		fullPath = fullPath.substr(fullPath.find_last_of("/")+1);
		rewards->setRom(fullPath);
	}
	
	// Check if there is anything on the screen 
	if(true){
		// Update screen (not really needed)
		system->frameBuffer().refresh();
		
		oldScreen = curScreen;
		curScreen = nextScreen(); 

    if (enable_stats) update_stats(); 
    
		rewards->update();
		
		// Get commands for next frame
		if(comm)
			comm->runEventLoop(this);
	}
}

Matrix AIBase::getRam(){
	Matrix dump;
	MatrixRow row;
	
	Debugger *db = &system->debugger();
	if(!db){
		return dump;
	}
	
	string tmp;
	for(int pos = 0x80;pos<0xff;pos++){
		row.push_back(db->peek(pos));
	}
	
	dump.push_back(row);
	return dump;
}

// Does the actual getting of the screen from Stella (without scaling)
Matrix AIBase::nextScreen(){
	int h = getScreenHeight();
	int w = getScreenWidth();

	//cout << "height and width reported as " << h << " " << w << endl; 

	Matrix curscr;
	
	for(int y=0;y<h;y++){
		MatrixRow row;
		int dx=0,dy=y;
		system->frameBuffer().translateCoords(dx, dy);
		if(dy==(int)curscr.size()){
			for(int x=0;x<w;x++){
				dx = x;
				dy = y;
				system->frameBuffer().translateCoords(dx, dy);
				if(dx==(int)row.size())
        {
				  int p = getPixel(x,y); 
          //cout << "pixel " << x << "," << y << " = " << p << endl; 
          row.push_back(p);
        }
			}
			curscr.push_back(row);
		}
	}
	
	return curscr;
}

Matrix AIBase::getScreen()
{
  return curScreen;
}

Matrix AIBase::getPrevScreen(){
	return oldScreen;
}

// Saves current game state in a stack
void AIBase::saveState(){
	system->debugger().saveState(saveStack++);
}

// Loads current game from the stack
void AIBase::loadState(){
	system->debugger().loadState(--saveStack);
}

// Gets the screen height without scaling
int AIBase::getScreenHeight(){
	return system->frameBuffer().baseHeight()*2;
}

// Gets the screen width without scaling
int AIBase::getScreenWidth(){
	return system->frameBuffer().baseWidth()*2;
}

// Wrapper for pressing key down
void AIBase::pressKey(SDLKey key){
	sendKey(key,true);
}

// Unpresses all keys
void AIBase::resetKeys(){
	sendKey(SDLK_UP,false);
	sendKey(SDLK_DOWN,false);
	sendKey(SDLK_RIGHT,false);
	sendKey(SDLK_LEFT,false);
	sendKey(SDLK_SPACE,false);
}

// Auxilary function that interacts with the system to press keys
void AIBase::sendKey(SDLKey key, bool press){
	SDL_Event event;
	if(press){
		event.type = SDL_KEYDOWN;
		event.key.type = SDL_KEYDOWN;
		event.key.state = SDL_PRESSED;
	}else{
		event.type = SDL_KEYUP;
		event.key.type = SDL_KEYUP;
		event.key.state = SDL_RELEASED;	
	}
	event.key.keysym.sym = key;
	SDL_PushEvent(&event);
}

// Gets the current keys being pressed (format: "Down-Up-Left-Right-Space")
bool AIBase::getKeys(){
	static bool up = false;
	static bool down = false;
	static bool left = false;
	static bool right = false;
	static bool space = false;
	
	// Get events
	SDL_PumpEvents();
	int count = SDL_PeepEvents(NULL,10,SDL_PEEKEVENT,SDL_ALLEVENTS);
	
	for(int i=0;i<count;i++){
		SDL_Event e;
		
		// Pop event from queue
		SDL_PeepEvents(&e,1,SDL_GETEVENT,SDL_ALLEVENTS);
		
		string key = SDL_GetKeyName(e.key.keysym.sym);
		if(!key.find("down",0))
			down = e.key.type==SDL_KEYDOWN;
		if(!key.find("up",0))
			up = e.key.type==SDL_KEYDOWN;
		if(!key.find("left",0))
			left = e.key.type==SDL_KEYDOWN;
		if(!key.find("right",0))
			right = e.key.type==SDL_KEYDOWN;
		if(!key.find("space",0))
			space = e.key.type==SDL_KEYDOWN;
		
		// Push event back to queue 
		SDL_PeepEvents(&e,1,SDL_ADDEVENT,0);
		
	}
	
	// Send current keys
	//printf("action %d%d%d%d%d\n",down,up,left,right,space);
	
	return count>0;
}

// Returns RGB value for particular position on the screen (with upscaling)
int AIBase::getPixel(int x, int y) {
	if(x>(int)system->frameBuffer().imageWidth() ||
	   y>(int)system->frameBuffer().imageHeight() || 
	   x<0 || y<0)
		return 0;
	
	SDL_Surface *surface = SDL_GetVideoSurface();
	
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;  

    switch(surface->format->BytesPerPixel){
		case 1:
			return *p;
			
		case 2:
			return *(Uint16 *)p;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			
		case 4:
			return *(Uint32 *)p;
		
		default:
			return 0;
    }
}

/** Stats computations... soon to be moved to agent-side **/

void AIBase::init_stats()
{
	ticks = 0; 
	maxColorsPerScreen = 0; 
  color_index = 0; 
  colstatsarr = NULL; 
}


void AIBase::update_stats()
{
  ticks++; 
  //if (ticks % 5 == 0)
  //updateUniqueTriplets();
  //if (ticks % 100 == 0)
  //updateUniqueCrossTriplets();
  updateUniquePatterns(3,3); 
  int c = getNumberColors(); 
  if (c > maxColorsPerScreen) maxColorsPerScreen = c; 
  if (ticks % 100 == 0) { 
    cout << "Unique ptriplets = " << uniqueTriplets.size() << ", patterns = " << uniquePatterns.size();  
    //int min, max; double avg; 
    //pixelStats(min, max, avg); 
    //cout << ", stats (min,max,avg) = " << min << "," << max << "," << avg; 
    cout << ", maxcps = " << maxColorsPerScreen << endl; 
  }
}


void AIBase::updateUniqueTriplets()
{
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
      // y indexes the row, x the column
			ptriplet pt = make_pair(make_pair(x,y), curScreen[y][x]); 
			uniqueTriplets.insert(pt); 
		}
	}
}

void AIBase::updateUniqueCrossTriplets()
{
// CROSSTRIPLETS defined in AIPattern.h .. uses GNU extension hash maps
// --> may not work on Mac, therefore disabled by default. 
//
#if CROSSTRIPLETS
  cout << "Updating cross triplets. " << endl; 

  if (colstatsarr == NULL)
  {
    cout << "Allocating memory.." << endl; 
    colstatsarr = new map<pair<int,int>, bool>*** [54];
    for (int i1 = 0; i1 < 54; i1++)
    {
      colstatsarr[i1] = new map<pair<int,int>, bool>** [36]; 
      for (int j1 = 0; j1 < 36; j1++)
      {
        colstatsarr[i1][j1] = new map<pair<int,int>, bool>* [54]; 
        for (int i2 = 0; i2 < 54; i2++)
        {
          colstatsarr[i1][j1][i2] = new map<pair<int,int>, bool> [36]; 
        }
      }
    }
  }


	for(size_t y = 0; y < curScreen.size(); y++){

    cout << y << " "; 
    fflush(stdout); 

		for(size_t x = 0; x < curScreen[y].size(); x++){

      // y indexes the row, x the column
			pair<int,int> first_pair = make_pair(x,y); 

      //cout << "UnCrTr: x,y = " << x << "," << y << endl; 
	
      for(size_t yp = 0; yp < curScreen.size(); yp++){
    		for(size_t xp = 0; xp < curScreen[yp].size(); xp++){

         
          if (x == xp && y == yp)
            continue; 

          // y indexes the row, x the column
          //pair<int,int> second_pair = make_pair(xp,yp); 
         
          //pcrosstriplet pct = make_pair(make_pair(first_pair, second_pair), curScreen[y][x]);
          //pcrosstriplet pct = make_pair(make_pair(first_pair, second_pair), curScreen[y][x]);
          //uniqueCrossTriplets.insert(pct);
         
          if (x % 6 == 0 && y % 6 == 0 && xp % 6 == 0 && yp % 6 == 0)
          {
            /*crosstriplet ct; 
            ct.x1 = x; ct.y1 = y; 
            ct.x2 = xp; ct.y2 = yp; 
            ct.color1 = curScreen[y][x]; ct.color2 = curScreen[yp][xp]; 

            uniqueCrossTriplets[ct] = true;
            */

            int color1 = curScreen[y][x];
            int color2 = curScreen[yp][xp];

            int c1index = color2indexmap[color1]; 
            int c2index = color2indexmap[color2]; 

            if (c1index == 0)
            {
              color_index++; 
              color2indexmap[color1] = c1index = color_index; 
            }
            
            if (c2index == 0)
            {
              color_index++; 
              color2indexmap[color2] = c2index = color_index; 
            }

            pair<int,int> cpair = make_pair(c1index,c2index); 

            (colstatsarr[x/6][y/6][xp/6][yp/6])[cpair] = true; 
          }

        }
      }
		}
	}

  cout << " .. Done. Computing num ... "; 
  fflush(stdout); 

  int num = 0; 

  for (int i1 = 0; i1 < 54; i1++)
    for (int i2 = 0; i2 < 54; i2++)
      for (int j1 = 0; j1 < 36; j1++)
        for (int j2 = 0; j2 < 36; j2++)
          num += colstatsarr[i1][j1][i2][j2].size();

  cout << "num = " << num << endl; 
#endif
}

void AIBase::updateUniquePatterns(int rows, int cols)
{
  // For overlapping, make row_inc = col_inc = 1 

  //int row_inc = rows, col_inc = cols; 
  int row_inc = 1, col_inc = 1; 

	for(size_t r = 0; r < curScreen.size(); r += row_inc){
		for(size_t c = 0; c < curScreen[r].size(); c += col_inc){
      //cout << curScreen.size() << " " << curScreen[y].size() << endl; 
      // --> Gives 210 320,
      
      vector<int> p;
      p.push_back(r); 
      p.push_back(c); 

      int maxrp = MIN(r+rows-1,curScreen.size()-1);  
      int maxcp = MIN(c+cols-1,curScreen[r].size()-1);  

      for (int rp = r; rp <= maxrp; rp++)
        for (int cp = c; cp <= maxcp; cp++)
          p.push_back(curScreen[rp][cp]); 

      uniquePatterns.insert(p); 
		}
	}
}

void AIBase::pixelStats(int & min, int & max, double & avg)
{
	min = 1000000; 
	max = -1; 
	avg = 0; 
	double sum = 0; 
	int num = 0; 
	
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
			
			cout << "pixelStats x,y = " << x << "," << y << endl; 
			
			int counts = 0; 
			set<ptriplet>::iterator iter; 
			
			for (iter = uniqueTriplets.begin(); 
				 iter != uniqueTriplets.end(); 
				 iter++) 
			{
				ptriplet pt = *iter; 
				int xp = pt.first.first; 
				int yp = pt.first.second; 
				
				if ((int)x == xp && (int)y == yp)
					counts++; 
			}
			
			if (counts < min)
				min = counts; 
			
			if (counts > max)
				max = counts; 
			
			sum += counts; 
			num++; 
		}
	}
	
	avg = sum/num; 
}

// Gets the number found in screen
int AIBase::getNumberColors()
{
	set<int> colors; 
	
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
			colors.insert(curScreen[y][x]); 
		}
	}
	
	return colors.size(); 
}



