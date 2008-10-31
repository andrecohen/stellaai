
#ifndef __AI_SETTINGS_H_
#define __AI_SETTINGS_H_

#include <string>
#include <fstream>

using namespace std;

class AISettings
{
public:
	static int get_int_setting(const std::string & key); 
private:
	static void open_file(); 
	static bool get_setting(const std::string & key, std::string & value); 
	static string get_default(const std::string & key);
	
	static string settings_file; 
	static ifstream input;  
}; 

#endif

