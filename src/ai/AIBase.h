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

class Debugger;

#include "AIComm.h"
#include "EventHandler.hxx"
#include "FrameBuffer.hxx"

class AIBase {
public:
	AIBase(EventHandler*, FrameBuffer*);
	~AIBase();
	void update(Debugger*,EventHandler*, FrameBuffer*);
	void commands();
	
	void sendFullScreen();
	void sendDiffScreen();
	
	void pressKey(SDLKey);
	void resetKeys();
	void sendKey(SDLKey,bool);
	bool getKeys();
	
	int getPixel(int,int);
	void drawPixel(int,int,Uint32);	
	void drawRectangle(int,int,int,int,Uint32);
	void drawLine(int,int,int,int,Uint32);
	
	FrameBuffer *frameBuffer;
	EventHandler *eventHandler;
	Debugger *debugger;
private:
	Matrix getScreen();
	int getScreenHeight();
	int getScreenWidth();
	
	AIComm *comm;
	Matrix screen;
};

#endif


