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

#ifndef DETECTION_H
#define DETECTION_H

#include <SDL/SDL.h>

#include "Scripting.h"
#include "Object.h"
#include "Grouping.h"

class Detection {
public:
	Detection(Grouping *);
	Detection(SDL_Surface *, char *);
	
	Objects update(SDL_Surface *);
	
	void groupPixels();
	
	int groupLines();
	
	Objects getObjects() { return objects; }

private:
	
	Objects updateLine(int, int, int, int);
	void linkLines(int, int);
	
	vector<int> aroundObject(Object *, int);
	
	Grouping *group;
	SDL_Surface *frame;
	Objects objects;
};


#endif