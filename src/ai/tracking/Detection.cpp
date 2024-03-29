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
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

using namespace std;

#include "Object.h"
#include "Detection.h"
#include "Grouping.h"

Uint32 getPixel(SDL_Surface *surface, int x, int y);

#define GROUP_DISTANCE	15

Detection::Detection(Grouping *_group) {
	group = _group;
}

Detection::Detection(SDL_Surface *screen, char *filename) {
	// Open file
	frame = IMG_Load(filename);
	if(frame == NULL) {
		printf("Error opening file");
		exit(0);
	}
	
	// Show image
	SDL_BlitSurface(frame, NULL, screen, NULL);
	SDL_Flip(screen);
	
	// Do detection
	update(frame);
	
	for(size_t i=0; i<objects.size(); i++)
		objects[i]->describe();
}

Objects Detection::update(SDL_Surface *_frame) {
	frame = _frame;
	clock_t t = clock();
	groupPixels();
	int change;
	int max = 0;
	while((change = groupLines())>0 && max++<5){
		// Keep grouping until no more changes are made
	}
	cout<<"Time: "<<(clock() - t)/(CLOCKS_PER_SEC/100)<<"ms"<<endl;
	
	return objects;
}

void Detection::groupPixels() {

	Lines lines;
	for(int y=0; y<frame->clip_rect.h; y++) {
		Objects line = updateLine(0, y, 1, 0);
		lines.push_back(line);
	}
	
	// Link 2 lines together
	for(size_t l=0; l+1<lines.size(); l++) {
		// For each object in line 1
		for(size_t o=0; o<lines[l].size(); o++) {
			Object *curr = lines[l][o];
	
			bool stop = 0;
			for(size_t o2=0; o2<lines[l+1].size() && !stop; o2++) {
				// If the objects touch and are of the same color
				if(curr->touches(lines[l+1][o2]) && curr->color==lines[l+1][o2]->color) {
					// If the object has not been linked before
					if(lines[l+1][o2]->parent == NULL) {
						curr->link.push_back(lines[l+1][o2]);
						lines[l+1][o2]->parent = curr;
					}
				}else if(lines[l+1][o2]->x+lines[l+1][o2]->w>curr->maxX()) {
					stop = 1;
				}
			}
		}
	}	

	
	// Build object from links
	for(size_t l=0; l<lines.size(); l++) {
		for(size_t o=0;o<lines[l].size(); o++) {
			if(lines[l][o]->parent==NULL) {
					objects.push_back(lines[l][o]->buildFromLink());
			}
		}
	}
	
	// Release old memory
	for(size_t l=0; l<lines.size(); l++)
		for(size_t o=0; o<lines[l].size(); o++)
			delete lines[l][o];
	
}

// Groups similar pixels together in a line
Objects Detection::updateLine(int x, int y, int dx, int dy) {
	Objects found;
	
	while(x<frame->clip_rect.w && y<frame->clip_rect.h) {
		Object *current = new Object(); 

		if(found.size()>0 && found.back()->color == getPixel(frame, x, y)) {
			found.back()->w = found.back()->w + dx;
			found.back()->h = found.back()->h + dy;
		} else {
			current->color = getPixel(frame, x, y);
			current->x = x;
			current->y = y;
			current->w = 1;
			current->h = 1;
			found.push_back(current);
		}
		
		// Next
		x = x + dx;
		y = y + dy;
	}
	
	return found;
}

// Attempts to group every object with every other object (yes.. unfortunately this is exponential)
int Detection::groupLines() {
	Objects updated;

	int change = objects.size();
	
	
	// For each object yet unchecked
	while(objects.size()) {
		// Pop object from stack
		Object *curr = objects[objects.size()-1];
		objects.pop_back();
		
		// Objects near current object
		vector<int> a = aroundObject(curr, GROUP_DISTANCE);
		
		for(int n=a.size()-1; n>=0; n--) {
			if(group->apply(curr, objects[a[n]])) {
				// Group both objects
				curr->group(objects[a[n]]);

				// Remove subsumed object
				objects.erase(objects.begin()+a[n]);
			}
		}
		
		// Push object to list of updated objects
		updated.push_back(curr);
	}

	
	objects = updated;
	
	return change - updated.size();
}

// Returns list of objects that are within specified distance
vector<int> Detection::aroundObject(Object *object, int distance) {
	vector<int> list;
	
	for(size_t i=0; i<objects.size(); i++) {
		if(object!=objects[i]) {
			double d = object->distance(objects[i]);	
			if(d<distance || object->touches(objects[i])){
				list.push_back(i);
			}
		}
	}
	return list;
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
    switch(bpp) {
		case 1:
			return *p;
			
		case 2:
			return *(Uint16 *)p;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			
			case 4:
			return *(Uint32 *)p;
			
			default:
			return 0;       /* shouldn't happen, but avoids warnings */
    }
}