#ifndef _UTIL_GUARD_
#define _UTIL_GUARD_

#include <iostream>
#include <string>

using namespace std;

//// ///////////////////////////////////////////////////
//// miniUtilities  class
//// ///////////////////////////////////////////////////
//// provides simple utility functions which are used
//// later on
//// ///////////////////////////////////////////////////

class miniUtilities   // contains minor file utilities
{
public:
  string iterative_name(string path,int i,string file_type=string(".png"))   // returns a string which contains path to an image from a given foldername and i, the numerical path
  {
    return string(sanitize_folder_path(path) +  "/" + to_string(i) + file_type);
  }

  string sanitize_folder_path(string path)   // sanitize the folder path, remove "/" in the last position if any, so iterative_name() can function better
  {
    int len = path.length();
    if(path[len-1] == '/')
    {
      path = path.substr(0,len-1);
    }
    return path;
  }

};

#endif
