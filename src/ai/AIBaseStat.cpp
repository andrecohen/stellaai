/*
 *  AIBaseStat.cpp
 *  stella
 *
 *  Created by Andre Cohen on 11/3/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "AIBaseStat.h"

#define  MIN(a,b)	((a) < (b) ? (a) : (b))

AIBaseStat::AIBaseStat(OSystem *system) {
	init(system);
	
	ticks = 0; 
	maxColorsPerScreen = 0; 
	color_index = 0; 
	colstatsarr = NULL; 
}


void AIBaseStat::update() {
	ticks++; 
	//if (ticks % 5 == 0)
	//updateUniqueTriplets();
	//if (ticks % 100 == 0)
	//updateUniqueCrossTriplets();
	updateUniquePatterns(3,3); 
	int c = getNumberColors(); 
	if (c > maxColorsPerScreen) maxColorsPerScreen = c; 
	if (ticks % 100 == 0) { 
		cout << "Unique ptriplets = " << uniqueTriplets.size() << ", patterns = " << uniquePatterns.size();  
		//int min, max; double avg; 
		//pixelStats(min, max, avg); 
		//cout << ", stats (min,max,avg) = " << min << "," << max << "," << avg; 
		cout << ", maxcps = " << maxColorsPerScreen << endl; 
	}
}

void AIBaseStat::updateUniqueTriplets()
{
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
			// y indexes the row, x the column
			ptriplet pt = make_pair(make_pair(x,y), curScreen[y][x]); 
			uniqueTriplets.insert(pt); 
		}
	}
}

void AIBaseStat::updateUniqueCrossTriplets()
{
	cout << "Updating cross triplets. " << endl; 
	
	if (colstatsarr == NULL)
	{
		cout << "Allocating memory.." << endl; 
		colstatsarr = new map<pair<int,int>, bool>*** [54];
		for (int i1 = 0; i1 < 54; i1++)
		{
			colstatsarr[i1] = new map<pair<int,int>, bool>** [36]; 
			for (int j1 = 0; j1 < 36; j1++)
			{
				colstatsarr[i1][j1] = new map<pair<int,int>, bool>* [54]; 
				for (int i2 = 0; i2 < 54; i2++)
				{
					colstatsarr[i1][j1][i2] = new map<pair<int,int>, bool> [36]; 
				}
			}
		}
	}
	
	
	for(size_t y = 0; y < curScreen.size(); y++){
		
		cout << y << " "; 
		fflush(stdout); 
		
		for(size_t x = 0; x < curScreen[y].size(); x++){
			
			// y indexes the row, x the column
			pair<int,int> first_pair = make_pair(x,y); 
			
			//cout << "UnCrTr: x,y = " << x << "," << y << endl; 
			
			for(size_t yp = 0; yp < curScreen.size(); yp++){
                for(size_t xp = 0; xp < curScreen[yp].size(); xp++){
					
					
					if (x == xp && y == yp)
						continue; 
					
					// y indexes the row, x the column
					//pair<int,int> second_pair = make_pair(xp,yp); 
					
					//pcrosstriplet pct = make_pair(make_pair(first_pair, second_pair), curScreen[y][x]);
					//pcrosstriplet pct = make_pair(make_pair(first_pair, second_pair), curScreen[y][x]);
					//uniqueCrossTriplets.insert(pct);
					
					if (x % 6 == 0 && y % 6 == 0 && xp % 6 == 0 && yp % 6 == 0)
					{
						/*crosstriplet ct; 
						 ct.x1 = x; ct.y1 = y; 
						 ct.x2 = xp; ct.y2 = yp; 
						 ct.color1 = curScreen[y][x]; ct.color2 = curScreen[yp][xp]; 
						 
						 uniqueCrossTriplets[ct] = true;
						 */
						
						int color1 = curScreen[y][x];
						int color2 = curScreen[yp][xp];
						
						int c1index = color2indexmap[color1]; 
						int c2index = color2indexmap[color2]; 
						
						if (c1index == 0)
						{
							color_index++; 
							color2indexmap[color1] = c1index = color_index; 
						}
						
						if (c2index == 0)
						{
							color_index++; 
							color2indexmap[color2] = c2index = color_index; 
						}
						
						pair<int,int> cpair = make_pair(c1index,c2index); 
						
						(colstatsarr[x/6][y/6][xp/6][yp/6])[cpair] = true; 
					}
					
				}
			}
		}
	}
	
	cout << " .. Done. Computing num ... "; 
	fflush(stdout); 
	
	int num = 0; 
	
	for (int i1 = 0; i1 < 54; i1++)
		for (int i2 = 0; i2 < 54; i2++)
			for (int j1 = 0; j1 < 36; j1++)
				for (int j2 = 0; j2 < 36; j2++)
					num += colstatsarr[i1][j1][i2][j2].size();
	
	cout << "num = " << num << endl; 

}

void AIBaseStat::updateUniquePatterns(int rows, int cols)
{
	// For overlapping, make row_inc = col_inc = 1 
	
	//int row_inc = rows, col_inc = cols; 
	int row_inc = 1, col_inc = 1; 
	
	for(size_t r = 0; r < curScreen.size(); r += row_inc){
		for(size_t c = 0; c < curScreen[r].size(); c += col_inc){
			//cout << curScreen.size() << " " << curScreen[y].size() << endl; 
			// --> Gives 210 320,
			
			vector<int> p;
			p.push_back(r); 
			p.push_back(c); 
			
			int maxrp = MIN(r+rows-1,curScreen.size()-1);  
			int maxcp = MIN(c+cols-1,curScreen[r].size()-1);  
			
			for (int rp = r; rp <= maxrp; rp++)
				for (int cp = c; cp <= maxcp; cp++)
					p.push_back(curScreen[rp][cp]); 
			
			uniquePatterns.insert(p); 
		}
	}
}

void AIBaseStat::pixelStats(int & min, int & max, double & avg)
{
	min = 1000000; 
	max = -1; 
	avg = 0; 
	double sum = 0; 
	int num = 0; 
	
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
			
			cout << "pixelStats x,y = " << x << "," << y << endl; 
			
			int counts = 0; 
			set<ptriplet>::iterator iter; 
			
			for (iter = uniqueTriplets.begin(); 
				 iter != uniqueTriplets.end(); 
				 iter++) 
			{
				ptriplet pt = *iter; 
				int xp = pt.first.first; 
				int yp = pt.first.second; 
				
				if ((int)x == xp && (int)y == yp)
					counts++; 
			}
			
			if (counts < min)
				min = counts; 
			
			if (counts > max)
				max = counts; 
			
			sum += counts; 
			num++; 
		}
	}
	
	avg = sum/num; 
}

// Gets the number found in screen
int AIBaseStat::getNumberColors()
{
	set<int> colors; 
	
	for(size_t y = 0; y < curScreen.size(); y++){
		for(size_t x = 0; x < curScreen[y].size(); x++){
			colors.insert(curScreen[y][x]); 
		}
	}
	
	return colors.size(); 
}

AIBase *AIBaseStat::parent() {
	return (AIBase *)this;
}