#include <trimat/matte_applier.h>

int main()
{
  Matte M = Matte(Image("data/b0.png"),Image("data/g0.png"),Image("data/b0_blank.png"),Image("data/g0_blank.png")); // quick initializations from filenames!
  M.apply_matte();    // apply matting to blue image, green image, blue and green background only images
  Image finalMask = M.get_alpha_mask(); // final alpha mask
  Image mattedImage = M.get_matted_image(); // matted image
  mattedImage.assign_name("Matted Image");  // name them
  finalMask.assign_name("Alpha Mask");  // name them
  finalMask.convert(CV_8UC1,255.0); // 8 bit pixel values
  mattedImage.convert(CV_8UC3,255.0); // 8 bit pixel values
  mattedImage.write("data/mattedImage.png");
  cout << "\n Matted Image has been written to data/mattedImage.png \n";
  finalMask.write("data/finalMask.png");  // write images
  cout << "\n finalMask has been written to data/finalMask.png \n";
  finalMask.show(); // show them
  return 0;
}
