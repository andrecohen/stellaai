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
#include <vector>
#include <time.h>
#include <ctime>
#include <math.h>
using namespace std;

#include "AIGlobal.h"
#include "AIBase.h"

#include <SDL/SDL_Events.h>
#include "FrameBuffer.hxx"
#include "EventHandler.hxx"
#include "Event.hxx"
#include "Debugger.hxx"

AIBase::AIBase(EventHandler *e, FrameBuffer *f){
	// Are we talking doing any sort of AI
	try{
		comm = new AIComm();
	}catch(exception e){
		comm = NULL;
	}
	
	// Reset connections to the outside world
	frameBuffer = NULL;
	eventHandler = NULL;
}

AIBase::~AIBase(){
	if(comm)		
		delete comm;
}

// Called at every frame
void AIBase::update(Debugger *d, EventHandler *e, FrameBuffer *f){
	// If connection is closed, then there is nothing to do
	if(comm==NULL)
		return;
	
	// Connect to the world if we haven't yet
	if(!frameBuffer || !eventHandler || !debugger){
		frameBuffer = f;
		eventHandler = e;
		debugger = d;
	}	
	
	// Check if there is anything on the screen 
	if(getPixel(200,200)){
		// Update screen (not really needed)
		f->refresh();
		
		// Get commands for next frame
		commands();
	}
}

// Called once per game cycle, interprets commands until the NEXT command is received
void AIBase::commands() {
	while(comm){
		string command = comm->receive();
		cerr<<"Command: "<<command<<endl;
		
		if(command == "NEXT")		return;
		else if(command == "QUIT")	exit(0);
		else if(command == "UP")	pressKey(SDLK_UP);
		else if(command == "DOWN")	pressKey(SDLK_DOWN);
		else if(command == "LEFT")	pressKey(SDLK_LEFT);
		else if(command == "RIGHT")	pressKey(SDLK_RIGHT);
		else if(command == "SPACE")	pressKey(SDLK_SPACE);
		else if(command == "RESET")	resetKeys();
		else if(command == "FULL_SCREEN")	sendFullScreen(); 
		else if(command == "DIFF_SCREEN")	sendDiffScreen();
		else if(command == "SAVE"){}
		else if(command == "PREV"){}
		else if(command == "DUMP"){}
		else
			printf("Command '%s' not understood\n",command.c_str());
	}
}

// Sends entire screen
void AIBase::sendFullScreen(){
	int h = getScreenHeight();
	int w = getScreenWidth();
	
	comm->sendPacket(h);
	comm->sendPacket(w);
	
	Matrix current = getScreen();
	
	comm->sendPacket(current);	
	screen = current;
}

// Sends the difference of pixels from the last full screen sent and now
void AIBase::sendDiffScreen(){
	int h = getScreenHeight();
	int w = getScreenWidth();
	Matrix current = getScreen();
	
	if(current.size()!=screen.size() &&  current[0].size()!=screen[0].size())
		return;
	 
	for(int y=0;y<h;y++){
		for(int x=0;x<w;x++){
			if(current[y][x] != screen[y][x]){
				comm->sendPacket(x);
				comm->sendPacket(y);
				comm->sendPacket(current[y][x]);
			}
		}
	}
	
	// Once all differences has been send -1 is sent
	comm->sendPacket(-1);
	
	// Saves new the current screen for next time
	screen = current;
}

// Does the actual getting of the screen from Stella (without scaling)
Matrix AIBase::getScreen(){
	int h = getScreenHeight();
	int w = getScreenWidth();
	Matrix current;
	
	for(int y=0;y<h;y++){
		MatrixRow row;
		int dx=0,dy=y;
		frameBuffer->translateCoords(dx, dy);
		if(dy==(int)current.size()){
			for(int x=0;x<w;x++){
				dx = x;
				dy = y;
				frameBuffer->translateCoords(dx, dy);
				if(dx==(int)row.size())
					row.push_back(getPixel(x, y));
			}
			current.push_back(row);
		}
	}
	
	return current;
}

// Gets the screen height without scaling
int AIBase::getScreenHeight(){
	return frameBuffer->baseHeight()*2;
}

// Gets the screen width without scaling
int AIBase::getScreenWidth(){
	return frameBuffer->baseWidth()*2;
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
	printf("action %d%d%d%d%d\n",down,up,left,right,space);
	
	return count>0;
}

/******************************************************************
	Some utility functions
******************************************************************/

void AIBase::drawRectangle(int x, int y, int h, int w, Uint32 pixel)
{
	for(int x1=x;x1<x+w;x1++){
		drawPixel(x1,y,pixel);
		drawPixel(x1,y+h,pixel);
	}
	for(int y1=y;y1<y+h;y1++){
		drawPixel(x,y1,pixel);
		drawPixel(x+w,y1,pixel);
	}
}

void AIBase::drawLine(int x1, int y1, int x2, int y2, Uint32 pixel)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	double error = 0;
	double derror = dy / dx;
	int y = y1;
	for(int x=x1;x<x2;x++){
		drawPixel(x,y,pixel);
		error = error + derror;
		if(.5<fabs(error)){
			y++; 
			error=-1;
		}
	}
}

void AIBase::drawPixel(int x, int y, Uint32 pixel)
{
	if(x>(int)frameBuffer->imageWidth() || y>(int)frameBuffer->imageHeight() || x<0 || y<0)
		return;
	
	SDL_Surface *surface = frameBuffer->getCurrentScreen();//SDL_GetVideoSurface();
	
    int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
    switch(bpp) {
		case 1:
			*p = pixel;
			break;
			
		case 2:
			*(Uint16 *)p = pixel;
			break;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
			
		case 4:
			*(Uint32 *)p = pixel;
			break;
    }
}

int AIBase::getPixel(int x, int y) {
	if(x>(int)frameBuffer->imageWidth() || y>(int)frameBuffer->imageHeight() || x<0 || y<0)
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

void AIBase::pressKey(SDLKey key){
	sendKey(key,true);
}

void AIBase::resetKeys(){
	sendKey(SDLK_UP,false);
	sendKey(SDLK_DOWN,false);
	sendKey(SDLK_RIGHT,false);
	sendKey(SDLK_LEFT,false);
	sendKey(SDLK_SPACE,false);
}

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