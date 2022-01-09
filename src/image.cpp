#include <trimat/image.h>

Image::Image()
{
  // default constructor, gives image_name as image

  image_name = "image";
}

Image::Image(string path)
{
  // parameterized constructor, initializes the image from a filepath
  //
  // input arguments:
  //    - path (string): the inputpath from where the image can be read and initialized
  // output arguments: None


  image_container = imread(path.data());
  image_name = "image";
}

Image::Image(Mat I)
{
  // parametrized constructor, initializes from a Mat
  //
  // input arguments:
  //   - I (Mat): the OpenCV Mat object from which to initialize the image from
  // output arguments: None

  image_container = I;
  image_name = "image";
}

Mat Image::get_image()
{
  // getter, returns the raw mat image
  //
  // input arguments: None
  // output arguments: None

  return image_container;
}

void Image::write(string path)
{
  // write an image to a filepath, checks to see if problem in doing so, exits if so
  //
  // input arguments:
  //   - path (string): the path to where to write the image to
  // output arguments: None


  if( imwrite(path.data(),image_container) != true)
  {
      cout << "\n Problem Writing image "<< image_name <<"results! Exiting!! Restart Code again, sorry!\n";
      exit(1);
  }
}

void Image::resize_image(double scale)
{
  // scale image by given scale, i.e. width*scale and height*scale
  //
  // input arguments:
  //   - scale (double): The scaling factor by which to scale the image to, is a double type and can have non integral values
  // output arguments: None

  resize(image_container,image_container,Size(),scale,scale);
}

// void Image::convertColor()

void Image::convert(int code,double scale)
{
  // convert image to another datatype, e.g. float to 8-bit pixel values, with scale for casting image values,scale is alpha paramater in convertTo function
  //
  // input arguments:
  //   - code (int): The numerical value to the OpenCV code specifying how to convert an image,i.e. what image type
  //   - scale (double,default value=1.0): The factor applied to the image intentisty values
  // output arguments: None

image_container.convertTo(image_container,code,scale);
}

void Image::normalize_image(int minrange,int maxrange,int code)
{
  // normalize an image container
  //
  // input arguments:
  //   - minrange (int): The minimum range to apply the normalization
  //   - maxrange (int): The maximum value to apply to the intensity based normalization
  //   - code (int): The OpenCV image code in numerical form specifying the image type
  // output arguments: None

normalize(image_container,image_container,minrange,maxrange,code);
}

void Image::show(int hold)
{
  // show an image based on hold amount,by default will be a blocking call which will wait for user input to proceed and keep showing image until then
  //
  // input arguments:
  //   - hold (int,default value=0): The amount of time to wait after displaying using imshow(), if not set, i.e. value is zero then makes a blocking call until user input is found
  // output arguments: None

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
  //
  // input arguments:
  //   - name (string): The name to give the Image container
  // output arguments: None

  image_name = name;
}

void Image::show_name()
{
  // show the name of the image
  //
  // input arguments: None
  // output arguments: None


  cout << "\nName of image: " << image_name.data() << " \n";
}

string Image::get_name()
{
  // get the name of an image, returns the image name
  //
  // input arguments: None
  // output arguments:
  //   - image_name (string): The name of the image to return
  //

  return image_name;
}
