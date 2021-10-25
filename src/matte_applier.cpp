#include <trimat/matte_applier.h>

Matte::Matte()   // empty construtor
{}

Matte::Matte(Image bg1, Image bg2, Image bg3, Image bg4)  // parameterized constructor
{
  // initializes the background images and the blank background images
  BG1 = bg1;
  BG2 = bg2;
  BG1_blank = bg3;
  BG2_blank = bg4;
}

Mat Matte::do_difference_matting(Mat I1,Mat I2,Mat B1,Mat B2,Mat & F)
{
    // does the actual triangulation matting, returns the alpha mask

    for(int i = 0; i < I1.rows; i++)
    {
        for(int j = 0; j < I1.cols; j++)
        {
            Mat b;
            Mat A = Mat::zeros(6,4,CV_32FC1);

                b.push_back(I1.at<Vec3f>(i,j)[2] - B1.at<Vec3f>(i,j)[2]);
                b.push_back(I1.at<Vec3f>(i,j)[1] - B1.at<Vec3f>(i,j)[1]);
                b.push_back(I1.at<Vec3f>(i,j)[0] - B1.at<Vec3f>(i,j)[0]);
                b.push_back(I2.at<Vec3f>(i,j)[2] - B2.at<Vec3f>(i,j)[2]);
                b.push_back(I2.at<Vec3f>(i,j)[1] - B2.at<Vec3f>(i,j)[1]);
                b.push_back(I2.at<Vec3f>(i,j)[0] - B2.at<Vec3f>(i,j)[0]);       // collects the RGB values from two images per pixel into 6 equations that are solved here

                A.at<float>(0,0) = 1; A.at<float>(0,1) = 0; A.at<float>(0,2) = 0; A.at<float>(0,3) = -B1.at<Vec3f>(i,j)[2];
                A.at<float>(1,0) = 0; A.at<float>(1,1) = 1; A.at<float>(1,2) = 0; A.at<float>(1,3) = -B1.at<Vec3f>(i,j)[1];
                A.at<float>(2,0) = 0; A.at<float>(2,1) = 0; A.at<float>(2,2) = 1; A.at<float>(2,3) = -B1.at<Vec3f>(i,j)[0];
                A.at<float>(3,0) = 1; A.at<float>(3,1) = 0; A.at<float>(3,2) = 0; A.at<float>(3,3) = -B2.at<Vec3f>(i,j)[2];
                A.at<float>(4,0) = 0; A.at<float>(4,1) = 1; A.at<float>(4,2) = 0; A.at<float>(4,3) = -B2.at<Vec3f>(i,j)[1];
                A.at<float>(5,0) = 0; A.at<float>(5,1) = 0; A.at<float>(5,2) = 1; A.at<float>(5,3) = -B2.at<Vec3f>(i,j)[0]; // populating the A matrix


            Mat x = A.inv(DECOMP_SVD)*b;      // solution to AX = b, solving for X which contains the matte and the alpha values
            F.at<Vec3f>(i,j)[2] = x.at<float>(0);
            F.at<Vec3f>(i,j)[1] = x.at<float>(1);
            F.at<Vec3f>(i,j)[0] = x.at<float>(2);
            alpha.at<float>(i,j) = x.at<float>(3);

        }

    }

    return alpha;
}

Image Matte::float_and_norm(Image I1)
{
  // returns the image after float converstion and 0,1 MINMAX normalization

  I1.convert(CV_32F);
  I1.normalize_image(0,1,NORM_MINMAX);
  return I1;
}

void Matte::trimatting(Image background1,Image background2,Image background1_blank,Image background2_blank)
{
  // a helper function which actually uses the do_difference_matting and takes care of intensity scaling and other initalizations as required

  background1 = float_and_norm(background1);
  background2 = float_and_norm(background2);
  background1_blank = float_and_norm(background1_blank);
  background2_blank = float_and_norm(background2_blank);
  Mat bg = background1.get_image();
  alpha = Mat::zeros(bg.rows,bg.cols,CV_32FC1);
  F = Mat::zeros(bg.size(), CV_32FC3);
  alpha = do_difference_matting(background1.get_image(), background2.get_image(),background1_blank.get_image(),background2_blank.get_image(),F);
  finalMask = Image(alpha);
  mattedImage = Image(F);
}

void Matte::apply_matte()
{
  // direct matting fucntion, in case you use this as an object

  trimatting(BG1,BG2,BG1_blank,BG2_blank);
}

Image Matte::get_matted_image()
{
  // getter, returns mattedImage

  return mattedImage;
}

Image Matte::get_alpha_mask()
{

    // getter, returns alpha mask

    return finalMask;
}