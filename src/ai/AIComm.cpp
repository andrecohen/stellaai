/*
 *  AIComm.cpp
 *  stella
 *
 *  Created by Andre Cohen on 12/7/07.
 *
 */
#include <iostream>
#include <string>
#include <vector>

#include "AIComm.h"

using namespace std;

// Default address & port
#define AI_SERVER	"127.0.0.1"
#define AI_PORT		1985

// Establishes connection with Server
AIComm::AIComm(){
	socket = new TCPSocket(AI_SERVER,AI_PORT);
	counter = 0;
}

// Closes network connections and also sends message to server that it is quitting
AIComm::~AIComm(){

}

// Recieves string of data
string AIComm::receive(){
	int id = getInt();
	
	if(counter+1!=id){
		cerr<<"Packet lost from ["<<counter<<"-"<<id<<"]"<<endl;
	}
	counter = id;
	int size = getInt();
	string data = getString(size);
	
	sendPacket(id);
	
	return data;
}

// Sends string packet
void AIComm::sendPacket(string line){
	sendInt(counter);
	sendChar('s');
	sendInt(line.length());
	for(size_t i=0;i<line.length();i++)
		sendChar(line[i]);
}

// Sends integer packet
void AIComm::sendPacket(int num){
	sendInt(counter);
	sendChar('i');
	sendInt(sizeof(int));
	sendInt(num);
}
 
// Sends integer matrix packet
void AIComm::sendPacket(Matrix array){
	sendInt(counter);
	sendChar('r');
	size_t h = array.size();
	size_t w = array[0].size();
	cerr<<h<<","<<w<<endl;
	sendInt(h);
	sendInt(w);
	for(size_t y=0;y<h;y++)
		for(size_t x=0;x<w;x++)
			sendInt(array[y][x]);
}

// Sends 1 integer - not to be used directly
void AIComm::sendInt(int num){
	num = (num>>24) | (num << 8 & 0x00FF0000) | (num >> 8 & 0x000FF00) | (num<<24);
	return socket->send(&num,sizeof(num));
}
		
// Sends 1 character - not to be used directly
void AIComm::sendChar(char ch){
	socket->send(&ch,sizeof(char));
}

// Gets integer packet
int AIComm::getInt(){
	int temp=0;
	socket->recv(&temp, sizeof(int));
	temp = (temp>>24) | (temp << 8 & 0x00FF0000) | (temp >> 8 & 0x000FF00) | (temp<<24);
	return temp;
}

// Gets string packet of size s
string AIComm::getString(int s){
	char ch;
	string str = "";

	while(str.length()<(size_t)s){
		if(socket->recv(&ch,1)==1)
			str += ch;
	}
	return str;
}
