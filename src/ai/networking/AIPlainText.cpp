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
#include <string>
#include <vector>

#include "AIProtocol.h"
#include "AIPlainText.h"
#include "AIBase.h"

using namespace std;

// Default address & port
#define AI_SERVER	"127.0.0.1"
#define AI_PORT		1985

// Establishes connection with Server
AIPlainText::AIPlainText(){
	counter = 0;
}

// Closes network connections and also sends message to server that it is quitting
AIPlainText::~AIPlainText(){
	if(socket)
		delete socket;

}

bool AIPlainText::connect(){
	socket = new TCPSocket(AI_SERVER,AI_PORT);
	return socket!=NULL;
}

bool AIPlainText::isConnected(){
	return socket!=NULL;
}

// Called once per game cycle, interprets commands until the NEXT command is received
void AIPlainText::runEventLoop(AIBase *base){
	while(isConnected()){
		string command = receive();
		
		if(command == "NEXT")		return;
		else if(command == "QUIT")	exit(0);
		else if(command == "UP")	base->pressKey(SDLK_UP);
		else if(command == "DOWN")	base->pressKey(SDLK_DOWN);
		else if(command == "LEFT")	base->pressKey(SDLK_LEFT);
		else if(command == "RIGHT")	base->pressKey(SDLK_RIGHT);
		else if(command == "SPACE")	base->pressKey(SDLK_SPACE);
		else if(command == "RESET")	base->resetKeys();
		else if(command == "FULL_SCREEN")	sendFullScreen(base->getScreen(),base->getScreenHeight(),base->getScreenWidth()); 
		else if(command == "DIFF_SCREEN")	sendDiffScreen(base->getPrevScreen(),base->getScreen());
		else if(command == "SAVE")	base->saveState();
		else if(command == "PREV")	base->loadState();
		else if(command == "DUMP")	sendRam(base->getRam());
		else
			printf("Command '%s' not understood\n",command.c_str());
	}
}

// Sends entire screen
void AIPlainText::sendFullScreen(Matrix current,int h, int w){
	sendPacket(h);
	sendPacket(w);
	sendPacket(current);	
}

// Sends the difference of pixels from the last full screen sent and now
void AIPlainText::sendDiffScreen(Matrix previous, Matrix current){
	Matrix diff;
  computeDiff(previous, current, diff);  

	// Send diff matrix
	sendPacket(diff);
}

// Sends RAM as an 1x64 integer matrix
void AIPlainText::sendRam(Matrix ram){
	sendPacket(ram);
	
}

// Recieves string of data
string AIPlainText::receive(){
	int id = getInt();
	
	if(counter+1!=id){
		cerr<<"Packet lost from ["<<counter<<"-"<<id<<"]"<<endl;
	}
	counter = id;
	
	char type = getChar();
	if(type!='s')
		cerr<<"Packet must be of type string!\n";
	
	int size = getInt();
	string data = getString(size);
	
	sendPacket(id);
	
	return data;
}

// Sends string packet
void AIPlainText::sendPacket(string line){
	sendInt(counter);
	sendChar('s');
	sendInt(line.length());
	for(size_t i=0;i<line.length();i++)
		sendChar(line[i]);
}

// Sends integer packet
void AIPlainText::sendPacket(int num){
	sendInt(counter);
	sendChar('i');
	sendInt(sizeof(int));
	sendInt(num);
}
 
// Sends integer matrix packet
void AIPlainText::sendPacket(Matrix array){
	if(array.size()<0)
		return;
	
	sendInt(counter);
	sendChar('r');
	size_t h = array.size();
	size_t w = array[0].size();
	
	sendInt(h);
	sendInt(w);
	for(size_t y=0;y<h;y++)
		for(size_t x=0;x<w;x++)
			sendInt(array[y][x]);
}

// Sends 1 integer - not to be used directly
void AIPlainText::sendInt(int num){
	num = (num>>24) | (num << 8 & 0x00FF0000) | (num >> 8 & 0x000FF00) | (num<<24);
	return socket->send(&num,sizeof(num));
}
		
// Sends 1 character - not to be used directly
void AIPlainText::sendChar(char ch){
	socket->send(&ch,sizeof(char));
}

// Gets integer 
int AIPlainText::getInt(){
	int temp=0;
	socket->recv(&temp, sizeof(int));
	temp = (temp>>24) | (temp << 8 & 0x00FF0000) | (temp >> 8 & 0x000FF00) | (temp<<24);
	return temp;
}

// Gets character
char AIPlainText::getChar(){
	int temp=0;
	socket->recv(&temp, 2);
	temp = temp>>8 | temp<<8;
	return temp;
}

// Gets string packet of size s
string AIPlainText::getString(int s){
	char ch;
	string str = "";

	while(str.length()<(size_t)s){
		if(socket->recv(&ch,1)==1)
			str += ch;
	}
	return str;
}
