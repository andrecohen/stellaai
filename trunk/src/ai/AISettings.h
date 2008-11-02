
#ifndef __AI_SETTINGS_H_
#define __AI_SETTINGS_H_

#include <string>
#include <fstream>

using namespace std;

class AISettings
{
public:
	AISettings();
	
	int get_int_setting(const std::string & key); 
private:
	void open_file(); 
	bool get_setting(const std::string & key, std::string & value); 
	string get_default(const std::string & key);
	
	string settings_file; 
	ifstream input;  
	
	AISettings *instance;
}; 

#endif

