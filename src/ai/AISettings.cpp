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
#include <sstream>

#include <stdlib.h>

#include "AISettings.h"

using namespace std; 

static AISettings *instance = NULL;

AISettings::AISettings(){
	settings_file  = "aisettings.txt";
}

AISettings *AISettings::getInstance() {
	if(instance==NULL)
		instance = new AISettings();
	return instance;
}

void AISettings::open_file()
{
	input.open(settings_file.c_str()); 
	if (!input.is_open())
	{
		cerr << "Error opening settings file " << settings_file << endl; 
		cerr << "Please create it in the current directory and add the required settings." << endl; 
		cerr << "eg., enabled_protocol=<int>      (see top of AIBase.cpp)"  << endl; 
	}
}

string AISettings::get_default(const std::string & key)
{
	if (key == "enabled_protocol")	return "1"; 
	if (key == "base_mode")			return "0";
	
	cerr << "AISettings: No default defined for key!" << endl; 
	return ""; 
}

bool AISettings::get_setting(const string & key, string & value)
{
	open_file(); 
	
	string line; 
	
	while( getline(input,line) )
	{
		if (line.at(0) == '#') 
			continue; 
		
		int eqindex = line.find("="); 
		string lkey = line.substr(0, eqindex); 
		string lval = line.substr(eqindex+1); 
		
		if (key == lkey)
		{
			value = lval; 
			input.close(); 
			return true; 
		}
	}
	
	input.close(); 
	value = get_default(key); 
	return false; 
}

int AISettings::get_int_setting(const std::string & key)
{
	string sval; 
	if (!get_setting(key, sval))
		cerr << "AISetting: key (" << key << ") not found! Using default: " << sval << endl;
	
	int value; 
	istringstream buffer(sval);
	buffer >> value;
	
	return value; 
}


