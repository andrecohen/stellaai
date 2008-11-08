/*
 *  Tracking.cpp
 *  ObjectTracker
 *
 *  Created by Andre Cohen on 11/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <vector>
#include <set>

#include "Object.h"
#include "Tracking.h"
#include "Matching.h"

using namespace std;

Tracking::Tracking(Objects A, Objects B) {
	matcher = new Matching("/Users/andre/ObjectTracker/ObjectTracker/scripts/Pitfall.Matching.lua");
	
	t1 = A;
	t2 = B;
}

Objects Tracking::update() {
	Objects final;
	
	set<string> types = objectTypes();

	for(set<string>::iterator type=types.begin(); type!=types.end(); type++) {
		Objects f = trackObject(*type);
		
		for(int i=0; i<f.size(); i++)
			final.push_back(f[i]);
	}
	
	return final;
}

Objects Tracking::trackObject(string type) {
	Objects final;
	
	for(int a=0; a<t1.size(); a++) {
		if(t1[a]->name == type) {
			int bestID = -1;
			double bestScore = 0;
			
			for(int b=0; b<t2.size(); b++){
				if(t2[b]!=t1[a] && t2[b]->name==type){
					double s = matcher->match(t1[a], t2[b]);
					if(bestID==-1 || s<bestScore) {
						bestID = b;
						bestScore = s;
					}
				}
			}
			
			
			if(bestID>-1) {
				cout<<"Match: ";t1[a]->describe();
				t2[bestID]->describe();cout<<endl;
			}
		}
	}
	
	// For each object A in t1 of type
		// For each object B in t2 of type
			// Calculate distance
		// Make best match for A to some object in t2
	
	return final;
}

set<string> Tracking::objectTypes() {
	set<string> list;
	
	for(int i=0; i<t1.size(); i++)
		list.insert(t1[i]->name);
	for(int i=0; i<t2.size(); i++)
		list.insert(t2[i]->name);
	
	return list;
}