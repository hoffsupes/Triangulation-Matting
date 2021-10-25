#include <trimat/matte_applier.h>

int main()
{
  Matte M = Matte(Image("data/b0.png"),Image("data/g0.png"),Image("data/b0_blank.png"),Image("data/g0_blank.png"));
  M.apply_matte();
  Image finalMask = M.get_alpha_mask();
  Image mattedImage = M.get_matted_image();
  mattedImage.assign_name("Matted Image");
  finalMask.assign_name("Alpha Mask");
  finalMask.convert(CV_8UC1,255.0);
  mattedImage.convert(CV_8UC3,255.0);
  mattedImage.write("data/mattedImage.png");
  finalMask.write("data/finalMask.png");
  finalMask.show();
  return 0;
}
