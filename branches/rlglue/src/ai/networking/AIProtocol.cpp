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

#include "AIProtocol.h"

void AIProtocol::computeDiff(const Matrix & previous, const Matrix & current, 
                             Matrix & result)
{
	// If the last screen is not available, then we can't do a diff
	if(current.size()!=previous.size() &&  current[0].size()!=previous[0].size()){
		return;
	}
	
	// Generate diff matrix
	for(size_t y=0;y<current.size();y++){
		for(size_t x=0;x<current[y].size();x++){
			if(current[y][x] != previous[y][x]){
				MatrixRow row;
				row.push_back(x);
				row.push_back(y);
				row.push_back(current[y][x]);
				result.push_back(row);
			}
		}
	}
	
  
}
