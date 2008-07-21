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