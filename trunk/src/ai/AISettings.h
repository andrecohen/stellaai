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

#ifndef __AI_SETTINGS_H_
#define __AI_SETTINGS_H_

#include <string>
#include <fstream>

using namespace std;

class AISettings
{
public:
	AISettings();
	static AISettings *getInstance();
	
	int get_int_setting(const std::string & key); 
private:
	void open_file(); 
	bool get_setting(const std::string & key, std::string & value); 
	string get_default(const std::string & key);
	
	string settings_file; 
	ifstream input;  
}; 

#endif

