
#ifndef __AI_SETTINGS_H_
#define __AI_SETTINGS_H_

#include <string>
#include <fstream>


class AISettings
{
  static std::string settings_file; 
  static std::ifstream input;  

  static void open_file(); 

  static bool get_setting(const std::string & key, std::string & value); 

  static std::string get_default(const std::string & key); 

public:
  
  static int get_int_setting(const std::string & key); 
}; 

#endif

