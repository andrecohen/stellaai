/*
 *  AICluster.cpp
 *  stella
 *
 *  Created by Andre Cohen on 10/22/07.
 *
 */

#include <iostream>
#include <math.h>
#include <sstream>
#include "AIGlobal.h"
#include "AIBase.h"
#include "AICluster.h"


AICluster::AICluster(AIBase *b) {
	base = b;
}

void AICluster::print() {
	Objects objs = getObjects(Any);
	
	for (size_t i=0;i<objs.size();i++) {
		//debug(objs[i]);
		
		base->putRectangle(objs[i]->dimension.min.x,objs[i]->dimension.min.y,RectHeight(objs[i]->dimension),RectWidth(objs[i]->dimension),0xcc0000);
	}
	
	//cout<<"get_contacts\n\n";
}

char ObjectTypeName[][16]={"Any","Undefined","Man","Log","Wall","Ladder","Scorpion","Croc","Water","Sand","Hole","Vine"};

void AICluster::debug(Object *a) {
	cout<<"add_object "<<ObjectTypeName[a->type]<<" "
		<<a->dimension.min.x<<" "<<a->dimension.min.y<<" "
		<<RectWidth(a->dimension)<<" "<<RectHeight(a->dimension)<<"\n";
}

/*
	previous items are <linked> with <current item index>
	current items are <used> when lined
*/

vector<string> AICluster::getDiff(Objects &prev, Objects &curr){
	vector<int> link, used;
	
	vector<string> diff;
	stringstream buf; 
	
	bool changes = false;
	link.resize(prev.size());
	used.resize(curr.size());
	fill(link.begin(),link.end(),-1);
	fill(used.begin(),used.end(),-1);
	
	for(size_t ac=0;ac<prev.size();ac++){
		int bestDist=-1;
		
		for(size_t bc=0;bc<curr.size();bc++){
			Object *a=prev[ac],*b=curr[bc];
			int dist = RectDistance(a->dimension,b->dimension);
			if(dist<0)dist = dist*-1;
			if(a->type==b->type && used[bc]==-1 /*&& dist<20*/ && (dist<bestDist || bestDist==-1)){
				bestDist = dist;
				link[ac] = bc;
			}
		}
		if(link[ac]!=-1)
			used[link[ac]]=0;
		
	}
	
	// deletes/updates
	for(size_t i=0;i<link.size();i++){
		if(link[i]==-1){
			changes = true;
			buf.str("");
			buf<<"remove_object "<<ObjectTypeName[prev[i]->type]<<" "<<prev[i]->dimension.min.x<<" "<<prev[i]->dimension.min.y;
			diff.push_back(buf.str());
		}
		else{
			int x = (curr[link[i]]->dimension.min.x-prev[i]->dimension.min.x),
				y = (curr[link[i]]->dimension.min.y-prev[i]->dimension.min.y),
				w = (RectWidth(curr[link[i]]->dimension)-RectWidth(prev[i]->dimension)),
				h = (RectHeight(curr[link[i]]->dimension)-RectHeight(prev[i]->dimension));
			
			if(true){
				changes = true;
				buf.str("");
				buf<<"update_object "<<ObjectTypeName[prev[i]->type]<<" "<<prev[i]->dimension.min.x<<" "<<prev[i]->dimension.min.y<<" "
					<<x<<" "<<y<<" "<<w<<" "<<h;
				diff.push_back(buf.str());
			}
		}
	}
	
	for(size_t i=0;i<used.size();i++){
		if(used[i]==-1){
			changes = true;
			buf.str("");
			buf<<"add_object "<<ObjectTypeName[curr[i]->type]<<" "
			<<curr[i]->dimension.min.x<<" "<<curr[i]->dimension.min.y<<" "
			<<RectWidth(curr[i]->dimension)<<" "<<RectHeight(curr[i]->dimension);
			diff.push_back(buf.str());
		}
	}
	return diff;
}


