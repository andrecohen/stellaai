/*
 *  AIComm.h
 *  stella
 *
 *  Created by Andre Cohen on 12/7/07.
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include "AISocket.h"
#include "AIGlobal.h"

using namespace std;


class AIComm {
public:
	AIComm();
	~AIComm();
	
	void sendPacket(string);
	void sendPacket(int);
	void sendPacket(Matrix);
	
	string receive();

private:
	int counter;
	
	int getInt();
	string getString(int);
	
	void sendInt(int);
	void sendChar(char);
	
	TCPSocket *socket;
};