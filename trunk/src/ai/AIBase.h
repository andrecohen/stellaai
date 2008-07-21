/*
 *  AIBase.h
 *  stella
 *
 *  Created by Andre Cohen on 10/2/07.
 *
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