
#ifndef __AI_SETTINGS_H_
#define __AI_SETTINGS_H_

#include <string>
#include <fstream>

using namespace std;

class AISettings {
public:
	static AISettings *getInstance();
	
	int get_int_setting(const std::string & key); 
	
private:
	AISettings();
	
	void open_file(); 
	bool get_setting(const std::string & key, std::string & value); 
	string get_default(const std::string & key); 

	string settings_file; 
	ifstream input;  
	static AISettings *instance;
}; 

#endif

