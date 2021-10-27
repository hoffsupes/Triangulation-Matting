#include <trimat/image.h>

Image::Image()
{
  // default constructor, gives image_name as image

  image_name = "image";
}

Image::Image(string path)
{
  // parameterized constructor, initializes the from a filepath

  image_container = imread(path.data());
  image_name = "image";
}

Image::Image(Mat I)
{
  // parametrized constructor, initializes from a Mat
  //

  image_container = I;
  image_name = "image";
}

Mat Image::get_image()
{
  // getter, returns the raw mat image

  return image_container;
}

void Image::write(string path)
{
  // write an image to a filepath, checks to see if problem in doing so, exits if so

  if( imwrite(path.data(),image_container) != true)
  {
      cout << "\n Problem Writing image "<< image_name <<"results! Exiting!! Restart Code again, sorry!\n";
      exit(1);
  }
}

void Image::resize_image(double scale)
{
  // scale image by given scale, i.e. width*scale and height*scale

  resize(image_container,image_container,Size(),scale,scale);
}

// void Image::convertColor()

void Image::convert(int code,double scale)
{
  // convert image to another datatype, e.g. float to 8-bit pixel values, with scale for casting image values,scale is alpha paramater in convertTo function

image_container.convertTo(image_container,code,scale);
}

void Image::normalize_image(int minrange,int maxrange,int code)
{
  // normalize an image container

normalize(image_container,image_container,minrange,maxrange,code);
}

void Image::show(int hold)
{
  // show an image based on hold amount,by default will be a blocking call which will wait for user input to proceed and keep showing image until then

  imshow(image_name.data(),image_container);

  if(!hold)
  {
    waitKey();
  }
  else
  {
    waitKey(hold);
  }
}

void Image::assign_name(string name)
{
  // assign a name to an image, given by a string name

  image_name = name;
}

void Image::show_name()
{
  // show the name of the image

  cout << "\nName of image: " << image_name.data() << " \n";
}

string Image::get_name()
{
  // get the name of an image, returns the image name

  return image_name;
}
