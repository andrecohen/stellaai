
#ifndef __AI_PATTERN_
#define __AI_PATTERN_

#include <vector>

#define CROSSTRIPLETS 0

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

#if CROSSTRIPLETS

typedef std::pair< std::pair< std::pair<int,int>, std::pair<int,int> > , int > pcrosstriplet; 

#include <ext/hash_map>
//#include <unordered_map>
#include <limits.h>

struct crosstriplet { int x1, y1, color1, x2, y2, color2; }; 

struct ctHash {
  size_t operator()(const crosstriplet &ct) const
  {
    return (ct.x1 ^ ct.y1 ^ ct.color1 ^ ct.x2 ^ ct.y2 ^ ct.color2); 
  }
};

struct ctEqual {
  bool operator()(const crosstriplet & ct1, const crosstriplet & ct2)
  { 
    return (   ct1.x1 == ct2.x1 && ct1.x2 == ct2.x2
            && ct1.y1 == ct2.y1 && ct1.y2 == ct2.y2
            && ct1.color1 == ct2.color1 && ct1.color2 == ct2.color2); 
  }
};

typedef __gnu_cxx::hash_map<crosstriplet, bool, ctHash, ctEqual > ct2boolmap; 
typedef __gnu_cxx::hash_map<int,int> int2intmap; 

#endif 

#endif

