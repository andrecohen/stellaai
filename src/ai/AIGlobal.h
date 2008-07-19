/*
 *  AIGlobal.h
 *  stella
 *
 *  Created by Andre Cohen on 10/18/07.
 *
 */

#ifndef AIGLOBAL_H
#define AIGLOBAL_H

#include <string>
#include <vector>
using namespace std;

class Centroid;
class AIBase;
class AIKmeans;

// Old, but still used
enum ObjectType {
	Any			= 0,
	Undefined	= 1,
	Man			= 2,
	Log			= 3,
	Wall		= 4,
	Ladder		= 5,
	Scorpion	= 6,
	Croc		= 7,	
	Water		= 8,
	Sand		= 9,
	Hole		= 10,
	Vine		= 11
};

/*******************************************************************
	Basic Structures
*******************************************************************/

struct Point{
	int x, y;
};

struct Rect {
	Point min,max;
};
 
struct Object {
	Rect dimension;
	ObjectType type;
};

typedef vector<int> MatrixRow;
typedef vector< MatrixRow > Matrix;

typedef std::vector<Centroid *> Centroids;
typedef std::vector<Object *> Objects;

/*******************************************************************
	Some simple macros 
*******************************************************************/

#define NewPoint(p)					p.x = 0; p.y = 0;
#define NewRect(rect)				NewPoint(rect.min);NewPoint(rect.max);
#define SetPoint(p,_x,_y)			p.x = _x; p.y = _y;
#define SetRect(rect,x1,y1,x2,y2)	SetPoint(rect.min,x1,y1);SetPoint(rect.max,x2,y2);
#define RectWidth(obj)				(obj.max.x - obj.min.x)
#define RectHeight(obj)				(obj.max.y - obj.min.y)
#define RectCenterX(obj)			(obj.min.x + RectWidth(obj)/2)
#define RectCenterY(obj)			(obj.min.y + RectHeight(obj)/2)
#define RectDistance(a,b)			(sqrt(pow(RectCenterX(a)-RectCenterX(b),2)+pow(RectCenterY(a)-RectCenterY(b),2)))
#define PointInSpan(c,from,to)		((c-from>=1 && c-to<=1)
#define PointInRect(p,rect)			(PointInSpan(p.x,rect.min.x,rect.max.x) && PointInSpan(p.y,rect.min.y,rect.max.y))



#endif