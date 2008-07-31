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
#include "AISocket.h"
#include "AIProtocol.h"
#include "AIBase.h"
#include "AIGlobal.h"

using namespace std;

class AIPlainText : public AIProtocol {
public:
	AIPlainText();
	~AIPlainText();
	
	virtual bool connect();
	virtual bool isConnected();
	virtual void runEventLoop(AIBase *);
	
	void sendPacket(string);
	void sendPacket(int);
	void sendPacket(Matrix);
	
	string receive();

private:
	void sendFullScreen(Matrix,int,int);
	void sendDiffScreen(Matrix,Matrix);
	void sendRam(Matrix);
	
	int getInt();
	char getChar();
	string getString(int);
	
	void sendInt(int);
	void sendChar(char);
	
	TCPSocket *socket;
	int counter;
};


