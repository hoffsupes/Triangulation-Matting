#ifndef _IMAGE_GUARD
#define _IMAGE_GUARD

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

//// ///////////////////////////////////////////////////
//// Image class
//// ///////////////////////////////////////////////////
//// Models an image using the typical Mat container
//// in OpenCV with some typically used operations
//// bundled together for convenience and made simpler than
//// with certain customizations
//// ///////////////////////////////////////////////////

class Image
{
  Mat image_container;  // the actual image
  string image_name;    // name of image

public:
  Image();    // default constructor
  Image(string);  // paramterized constructor
  Image(Mat);   // paramterized constructor
  Mat get_image();  // get the original Mat containing the image
  void write(string); // write the image to a path
  void convert(int code,double scale=1.0);  // covert the image to another data type, e.g. float to 8-bit pixel value, scale by the scaling factor
  void normalize_image(int,int,int);    // normalize the image, min and max values and method provided, to be used with NORM_MINMAX
  void show(int hold=0);    // display an image along with wait times in ms
  void assign_name(string);   // assign a name to a given image
  string get_name();  // get the name of an image
  void show_name(); // show the name of an image
  void resize_image(double);    // scale the image as per the scale given
};
#endif
