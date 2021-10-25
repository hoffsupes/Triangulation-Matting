#ifndef _MATTE_GUARD_
#define _MATTE_GUARD_

#include <trimat/image.h>
#include <stdlib.h>

//// ///////////////////////////////////////////////////////////////
//// Matte class
//// ///////////////////////////////////////////////////////////////
//// Derives from the Image class and provides capability
//// to apply triangulation matting, i.e. solving for values
//// of alpha and foreground values using two images resulting in
//// six equations per pixel (due to RGB values per pixel), from:
//// Result_1 = alpha*foreground + (1-alpha)*background_1;
//// Result_2 = alpha*foreground + (1-alpha)*background_2;
//// here, Result_1, Result_2, background_1, background_2 are known
//// which is modeled as AX=b and
//// we solve for X as X = A_inverse * b
//// ///////////////////////////////////////////////////////////////

class Matte
{
  Image BG1;   // image with background1
  Image BG2;   // image with background2
  Image BG1_blank;   // background1 blank image
  Image BG2_blank;   // background2 blank image
  Mat alpha;   // alpha mask
  Mat F;   // Mat image where intrmediate results stored
  Image mattedImage,finalMask;   // the final matted image and alpha results stored here
  Mat do_difference_matting(Mat,Mat,Mat,Mat,Mat&);   // actual private internal matting function which does the triangulation matting

public:
  Matte();   // default constructor
  Matte(Image,Image,Image,Image);   // parameterized construtor
  Image float_and_norm(Image);   // convert image to flot and normalize between 0 and 1, easier to process them this way
  void trimatting(Image,Image,Image,Image);   // perform triangulation matting
  void apply_matte();   // apply the matte
  Image get_matted_image();   // return the matted image, mattedImage
  Image get_alpha_mask();   // return the alpha mask, finalMask
};

#endif
