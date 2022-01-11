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
  string iterative_name(string path,int i,string file_type=string(".png"))
  {
    /**
    returns a string which contains path to an image from a given foldername and i, the numerical path

    input arguments:
       - path (string): Path preceding name of image, e.g. for /path/folder/1.jpg it would be /path/foler, i.e. the folder where the results are stored
       - i (int): The index of the given element to be referred to , e.g. image_1 or image_2 etc.
       - file_type (string): The extension of the file, denoting the filetype

    output arguments:
       - output_path (string): The combined image path created from combining all of the above, for a given element i, e.g. /path/to/i.jpg

    */
    return string(sanitize_folder_path(path) +  "/" + to_string(i) + file_type);
  }

  string sanitize_folder_path(string path)
  {
    /**
    sanitize the folder path, remove "/" in the last position if any, so iterative_name() can function better

    input arguments:
       - path (string): The input path to be sanitized
    output arguments:
       - path (string): The sanitized output path

    */
    int len = path.length();
    if(path[len-1] == '/')
    {
      path = path.substr(0,len-1);
    }
    return path;
  }

};

#endif
