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
#include <vector>
#include <set>

#include "Object.h"
#include "Tracking.h"
#include "Matching.h"

using namespace std;

Tracking::Tracking(Objects A, Objects B, Matching *_matcher) {
	matcher = _matcher;
	t1 = A;
	t2 = B;
}

Objects Tracking::update() {
	Objects final;
	
	set<string> types = objectTypes();

	for(set<string>::iterator type=types.begin(); type!=types.end(); type++) {
		Objects f = trackObject(*type);
		
		for(size_t i=0; i<f.size(); i++)
			final.push_back(f[i]);
	}
	
	return final;
}

Objects Tracking::trackObject(string type) {
	Objects final;
	
	for(size_t a=0; a<t1.size(); a++) {
		if(t1[a]->name == type) {
			int bestID = -1;
			double bestScore = 0;
			
			for(size_t b=0; b<t2.size(); b++){
				if(t2[b]!=t1[a] && t2[b]->name==type){
					double s = matcher->match(t1[a], t2[b]);
					if(bestID==-1 || s<bestScore) {
						bestID = b;
						bestScore = s;
					}
				}
			}
			
			
			if(bestID>-1) {
				//cout<<"Match: ";t1[a]->describe();
				//t2[bestID]->describe();cout<<endl;
			}
		}
	}
	
	return final;
}

set<string> Tracking::objectTypes() {
	set<string> list;
	
	for(size_t i=0; i<t1.size(); i++)
		list.insert(t1[i]->name);
	for(size_t i=0; i<t2.size(); i++)
		list.insert(t2[i]->name);
	
	return list;
}