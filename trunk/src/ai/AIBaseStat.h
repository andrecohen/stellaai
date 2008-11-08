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

#ifndef _AIBASESTAT_H_
#define _AIBASESTAT_H_

#include <ext/hash_map>
#include <tr1/unordered_map>
#include <limits.h>
#include "AIBase.h"

using namespace std;
using namespace __gnu_cxx;

typedef pair< pair<int,int> , int > ptriplet; 
typedef vector< vector<int> > pattern; 
typedef pair< pair< pair<int,int>, pair<int,int> > , int > pcrosstriplet; 

struct crosstriplet { int x1, y1, color1, x2, y2, color2; }; 

struct ctHash {
	size_t operator()(const crosstriplet &ct) const
	{
		return (ct.x1 ^ ct.y1 ^ ct.color1 ^ ct.x2 ^ ct.y2 ^ ct.color2); 
	}
};

struct ctEqual {
	bool operator()(const crosstriplet & ct1, const crosstriplet & ct2)
	{ 
		return (   ct1.x1 == ct2.x1 && ct1.x2 == ct2.x2
				&& ct1.y1 == ct2.y1 && ct1.y2 == ct2.y2
				&& ct1.color1 == ct2.color1 && ct1.color2 == ct2.color2); 
	}
};

typedef hash_map<crosstriplet, bool, ctHash, ctEqual > ct2boolmap; 
typedef hash_map<int,int> int2intmap; 


class AIBaseStat : public AIBase {
public:
	AIBaseStat(OSystem *);
	
	virtual void update();
	
private:
	AIBase *parent();
	
	void updateUniqueTriplets(); 
	void updateUniqueCrossTriplets(); 
	void updateUniquePatterns(int rows, int cols); 
	int getNumberColors(); 
	void pixelStats(int & min, int & max, double & avg); 
	
	int ticks; 
	int maxColorsPerScreen;
	set<ptriplet> uniqueTriplets; 
	set< vector<int> > uniquePatterns;   
	map<int,int> color2indexmap; 
	map< pair<int,int> , bool > **** colstatsarr;
	int color_index; 
	
};


#endif