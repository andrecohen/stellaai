
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
