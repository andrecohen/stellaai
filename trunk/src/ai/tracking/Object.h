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

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
using namespace std;

class Object {
public:
	Object();
	Object(Object *);
	
	int maxX() { return x+w; }
	int maxY() { return y+h; }
	
	bool touches(Object *);
	double distance(Object *);
	double distance(int, int);
	void group(Object *);
	
	Object *buildFromLink();
	void describe();
	
	int x, y, w, h;
	unsigned int color;
	string name;
	int uid;
	
	vector<Object *> link;
	Object *parent;
	bool visited;
};

typedef vector< Object *> Objects;
typedef vector< Objects > Lines;

#endif