/*
 *  AIRewards.cpp
 *  stella
 *
 *  Created by Andre Cohen on 7/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <ctime>
using namespace std;

#include "AIRewards.h"
#include "OSystem.hxx"
#include "Debugger.hxx"
#include "CpuDebug.hxx"

AIRewards::AIRewards(OSystem *system){
	this->system = system;
	loadData();
	currentGame = NULL;
}

AIRewards::~AIRewards(){
	for(size_t i=0;i<games.size();i++)
		delete games[i];
}

void AIRewards::loadData(){
	ifstream file("rewards.txt");
	string rowType,temp;
	int address;
	RewardGame *game = NULL;
	
	if(!file.is_open()){
		cerr<<"Error opening rewards file.\n";
		return;
	}
	
	while(!file.eof()){
		file>>rowType;
		if(rowType=="ROM:"){
			if(game)
				games.push_back(game);
			game = new RewardGame();
			file>>game->filename;
			
		}else if(rowType=="TIME:" || rowType=="SCORE:"){
			RewardEntry entry;
			bool endEntry = false;
			
			if(rowType=="TIME:")	entry.type=Time;
			if(rowType=="SCORE:")	entry.type=Score;
			
			while(!endEntry && !file.eof()){
				streampos pos = file.tellg();
				file>>temp;
				
				for(string::iterator i = temp.begin();i!=temp.end();i++){
					if((*i)==';')
						endEntry = true;
				}
				
				file.seekg(pos);
				
				file>>hex>>address;
				entry.locations.push_back(address);			
			}
			file>>temp;
			game->entries.push_back(entry);
		}
	}
	if(game)
		games.push_back(game);

	file.close();
}

int AIRewards::getReward(string filename, RewardType type){
	// If we know the game reward locations then get them
	if(currentGame){
		return getReward(type);
	}else{
		// Find current game and save it for future queries
		for(size_t i=0;i<games.size() && !currentGame;i++){
			
			if(games[i]->filename==filename)
				currentGame = games[i];
		}
		// Make sure rewards are known for the current game
		if(currentGame)
			return getReward(type);
		else
			cerr<<"Game has no specified rewards!\n";
	}
	return 0;
}

int AIRewards::getReward(RewardType type){
	int entry = -1;
	string reward = "";
	// Find the reward we are looking for
	for(size_t i=0;i<currentGame->entries.size() && entry<0;i++){
		if(currentGame->entries[i].type==type)
			entry = i;
	}
	
	// Append each byte together
	for(size_t i=0;i<currentGame->entries[entry].locations.size();i++){
		int temp = system->debugger().peek(currentGame->entries[entry].locations[i]);
		// Debugger gives a hex value of a dec number -> hex(hex(dec)) = dec
		reward += Debugger::to_hex_4(temp);
	}
	
	// Return integer value
	return atoi(reward.c_str());
}

