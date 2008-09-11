
#ifndef __AI_PATTERN_
#define __AI_PATTERN_

#include <vector>

typedef std::pair< std::pair<int,int> , int > ptriplet; 

typedef std::vector< std::vector<int> > pattern; 


/* A pattern is a shape of pixels on the screen */

/*
 Doesn't work for our purposes yet because can't be considered unique 
 when using std::set (must look into proper overloading of operators for
 user-defined types)

class AIPattern
{
  int rows, cols; 

  // Assume rectangular; need to use vectors for set comparisons in AIBase
  std::vector< std::vector< int > values; 

  void init(); 

public: 
  AIPattern(int _rows, int _cols); 
  virtual ~AIPattern(); 

  void set_val(int row, int col, int color); 
};
*/

#endif

