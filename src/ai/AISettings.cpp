
#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>

#include <AISettings.h>

using namespace std; 

string AISettings::settings_file = "aisettings.txt"; 
ifstream AISettings::input; 
  
void AISettings::open_file()
{
  input.open(settings_file.c_str()); 
  if (!input.is_open())
  {
    cerr << "Error opening settings file " << settings_file << endl; 
    cerr << "Please create it in the current directory and add the required settings." << endl; 
    cerr << "eg., enabled_protocol=<int>      (see top of AIBase.cpp)"  << endl; 
    cerr << "" << endl; 

    exit(-1); 
  }
}
  
string AISettings::get_default(const std::string & key)
{
  if (key == "enabled_protocol") return "1"; 

  cerr << "AISettings: No default defined for key!" << endl; 
  return ""; 
}

bool AISettings::get_setting(const string & key, string & value)
{
  open_file(); 

  string line; 

  while( getline(input,line) )
  {
    if (line.at(0) == '#') 
      continue; 

    int eqindex = line.find("="); 
    string lkey = line.substr(0, eqindex); 
    string lval = line.substr(eqindex+1); 

    if (key == lkey)
    {
      value = lval; 
      input.close(); 
      return true; 
    }
  }

  input.close(); 
  value = get_default(key); 
  return false; 
}

int AISettings::get_int_setting(const std::string & key)
{
  string sval; 
  if (!get_setting(key, sval))
    cerr << "AISetting: key (" << key << ") not found! Using default: " << sval << endl;

  int value; 
  istringstream buffer(sval);
  buffer >> value;

  return value; 
}


