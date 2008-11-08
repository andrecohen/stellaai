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

#include "Tracker.h"
#include "Detection.h"
#include "Tracking.h"

using namespace std;

Tracker::Tracker(string rom) {
	string name = rom.substr(0, rom.find(".bin"));
	grouper = new Grouping(("tracker/"+name+".Grouping.lua").c_str());
	matcher = new Matching(("tracker/"+name+".Matching.lua").c_str());	
}


Objects Tracker::update(SDL_Surface *screen) {
	Detection detection(grouper);
	Objects current = detection.update(screen);
	cout<<"Detected: "<<current.size();
	
	for(int i=0; i<current.size(); i++)
		if(current[i]->name.size()==0)
			current[i]->describe();
	
	if(previous.size()>0) {
		Tracking tracking(previous, current, matcher);
		current = tracking.update();
		cout<<"Tracked: "<<current.size()<<endl;
	}
	
	previous = current;
	
	return current;
}
