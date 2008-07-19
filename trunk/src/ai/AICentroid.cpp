/*
 *  AICentroid.cpp
 *  stella
 *
 *  Created by Andre Cohen on 10/18/07.
 *
 */

#include <math.h>

#include "AIGlobal.h"
#include "AICentroid.h"
#include "AIBase.h"
#include "AIKmeans.h"

Centroid::Centroid(int w, int h){
	center.x = w;
	center.y = h;
	avg.x = 0;
	avg.y = 0;
	
	SetRect(dim,-1,-1,-1,-1);
	
	count = 0;
	type = Undefined;
}

void Centroid::addPoint(int x, int y) {
	SetPoint(avg,avg.x+x,avg.y+y);
	count++;
	
	// Rectangle
	if(dim.min.x==-1){
		SetRect(dim,x,y,x,y);
	}
	else if(x<dim.min.x)	dim.min.x=x;
	else if(x>dim.max.x)	dim.max.x=x;
	else if(y<dim.min.y)	dim.min.y=y;
	else if(y>dim.max.y)	dim.max.y=y;
	
}

double Centroid::recenter() {
	if (count>0) {
		Point p;
		p.x = ((avg.x/count)+center.x)/2;
		p.y = ((avg.y/count)+center.y)/2;
		
		double d = fabs((p.x-center.x)+(p.y-center.y));
		
		center = p;
		
		NewPoint(avg);
		count = 0;
		
		return d;
	}
	return -1;
}

int Centroid::getWidth(){
	return RectWidth(dim);
}
int Centroid::getHeight(){
	return RectHeight(dim);
}

void Centroid::print(AIBase *aiBase, bool text, bool graph) {
	if (type!=Undefined) {
		if (graph)
			aiBase->putRectangle(center.x,center.y,10,10,0xcc0000);
		if (text)
			cout<<type<<": "<<center.x<<", "<<center.y<<"\t"<<getWidth()<<"x"<<getHeight()<<"\n";
	}
}