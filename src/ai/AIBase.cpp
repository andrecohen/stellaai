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
#include <zlib.h>
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


static int enabled_protocol;

AIBase::AIBase() {
}

AIBase::AIBase(OSystem *system){
	init(system);
}

void AIBase::init(OSystem *system) {
	comm = NULL; 
	
	AISettings *settings = new AISettings();
	enabled_protocol = settings->get_int_setting("enabled_protocol"); 
	
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
	
	// Detect rom being played for loading script file
	if(rewards->isRomSet()==false && system->romFile()!=""){
		string fullPath = system->romFile();
		fullPath = fullPath.substr(fullPath.find_last_of("/")+1);
		rewards->setRom(fullPath);
	}
	
	if(true){
		// Update screen (not really needed)
		//system->frameBuffer().refresh();
		
		oldScreen = curScreen;
		curScreen = nextScreen(); 
	
		//compress(curScreen);
		
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
					row.push_back(p);
				}
			}
			curscr.push_back(row);
		}
	}
	
	return curscr;
}

Matrix AIBase::getScreen() {
  return curScreen;
}

Matrix AIBase::getPrevScreen() {
	return oldScreen;
}

// Saves current game state in a stack
void AIBase::saveState() {
	system->debugger().saveState(saveStack++);
}

// Loads current game from the stack
void AIBase::loadState() {
	system->debugger().loadState(--saveStack);
}

// Reloads emulator with current ROM
void AIBase::restartEmulation() {
	system->deleteConsole();
	system->createConsole();
}

// Gets the screen height without scaling
int AIBase::getScreenHeight() {
	return system->frameBuffer().baseHeight()*2;
}

// Gets the screen width without scaling
int AIBase::getScreenWidth() {
	return system->frameBuffer().baseWidth()*2;
}

// Wrapper for pressing key down
void AIBase::pressKey(SDLKey key) {
	sendKey(key,true);
}

// Unpresses all keys
void AIBase::resetKeys() {
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

vector<unsigned char> AIBase::compress(Matrix vdata) {
	uLong length = vdata.size()*vdata[0].size();
	int *from = (int *)calloc(length,sizeof(int));
	int *to = (int *)calloc(ceil(length*1.01)+12,sizeof(int));
	
	// Copy to a byte array 
	for(uint y=0;y<vdata.size();y++)
		for(uint x=0;x<vdata[y].size();x++)
			from[y*vdata[y].size()+x] = vdata[y][x];
	
	// Compress
	uLong resultLength = length*2;
	compress2((Bytef *)to, &resultLength, (Bytef *)from, length*2, 9);
	
	// Pass compressed data into vector
	vector<unsigned char> result;
	for(uLong n=0;n<resultLength;n++)
		result.push_back(to[n]);
		
	//cout<<"From: "<<length<<" to "<<resultLength<<endl;
	
	// Free byte array
	free(from);
	free(to);

	return result;
}

