#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <sys/stat.h> /// dont know if you"ll find this in windows so try running this on linux or find another alternative to mkdir in windows

using namespace std;
using namespace cv;


Mat do_difference_matting(Mat I1,Mat I2,Mat B1,Mat B2,Mat & F, int disp)
{

    I1.convertTo(I1,CV_32F);
    normalize(I1,I1,0,1,NORM_MINMAX);
    I2.convertTo(I2,CV_32F);
    normalize(I2,I2,0,1,NORM_MINMAX);

    

    Mat alpha;
    alpha = Mat::zeros(I1.rows,I1.cols,CV_32FC1);
    F = Mat::zeros(I1.size(), CV_32FC3);
    
    int weprog = 0;
    
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
                b.push_back(I2.at<Vec3f>(i,j)[0] - B2.at<Vec3f>(i,j)[0]);
        
                A.at<float>(0,0) = 1; A.at<float>(0,1) = 0; A.at<float>(0,2) = 0; A.at<float>(0,3) = -B1.at<Vec3f>(i,j)[2];
                A.at<float>(1,0) = 0; A.at<float>(1,1) = 1; A.at<float>(1,2) = 0; A.at<float>(1,3) = -B1.at<Vec3f>(i,j)[1];
                A.at<float>(2,0) = 0; A.at<float>(2,1) = 0; A.at<float>(2,2) = 1; A.at<float>(2,3) = -B1.at<Vec3f>(i,j)[0];
                A.at<float>(3,0) = 1; A.at<float>(3,1) = 0; A.at<float>(3,2) = 0; A.at<float>(3,3) = -B2.at<Vec3f>(i,j)[2];
                A.at<float>(4,0) = 0; A.at<float>(4,1) = 1; A.at<float>(4,2) = 0; A.at<float>(4,3) = -B2.at<Vec3f>(i,j)[1];
                A.at<float>(5,0) = 0; A.at<float>(5,1) = 0; A.at<float>(5,2) = 1; A.at<float>(5,3) = -B2.at<Vec3f>(i,j)[0];
                
        
            Mat x = A.inv(DECOMP_SVD)*b;
            F.at<Vec3f>(i,j)[2] = x.at<float>(0);
            F.at<Vec3f>(i,j)[1] = x.at<float>(1);
            F.at<Vec3f>(i,j)[0] = x.at<float>(2);
            alpha.at<float>(i,j) = x.at<float>(3);
            
        weprog++;    
        
        if(weprog % 1000 == 0 && disp == 1)
        {
            cout << "\n Progress on Frame:: " << 100*( float((i*I1.cols)+j)/float(I1.rows*I1.cols)) << "% " << "\n";
            
        }
        
        }
        
    }
    

    return alpha;
}

void make_images_nik(Mat & I1,Mat & I2, Mat & I3,Mat & I4,float siz = 0.5)
{
    
    resize(I1,I1,Size(0,0),siz,siz);
    resize(I2,I2,Size(0,0),siz,siz);
    resize(I3,I3,Size(0,0),siz,siz);
    resize(I4,I4,Size(0,0),siz,siz);
     
}

int tfxn()
{
    
    Mat I1 = imread("/home/hulio/Downloads/diff-matte/b0.png");
    Mat I2 = imread("/home/hulio/Downloads/diff-matte/g0.png");
    Mat B2 = imread("/home/hulio/Downloads/diff-matte/g0_blank.png");
    Mat B1 = imread("/home/hulio/Downloads/diff-matte/b0_blank.png");
    Mat F;
//     make_images_nik(I1,I2,B1,B2,0.5); %% If you want to resize a single frame of a very large image to see if it works

    Mat alpha = do_difference_matting(I1,I2,B1,B2,F,1);
    
    normalize(alpha,alpha,0,255,NORM_MINMAX);
    alpha.convertTo(alpha,CV_8UC1);
    
    imshow("alpha mask",alpha);
        waitKey();
    
    return 1;
}

int main()
{

if(mkdir("Results",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){ cout << "\n Result Folder cannot be created!! \n";}
if(mkdir("Results/Matte",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){ cout << "\n Matte Folder cannot be created!! \n";} /// If either of these errors raised then delete these lines, create these folders in the current working directory from which you execute the code and then proceed from the beginning
if(mkdir("Results/Foreground",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)!=0){ cout << "\n Matte Folder cannot be created!! \n";} /// If either of these errors raised then delete these lines, create these folders in the current working directory from which you execute the code and then proceed from the beginning

VideoCapture cap_I1;
VideoCapture cap_I2;

Mat B1,B2;
B1 = imread("Path to your BG1 only colors image");
B2 = imread("Path to your BG2 only colors image");

cap_I1.open("Path to your B1 scene");
cap_I2.open("Path to your B2 scene");
    
// VideoWriter wri; <---- To save results as an video file//
// int codec = CV_FOURCC("M","J","P","G");
// wri.open("Final_Results.avi",codec,cap_I1.get(CV_CAP_PROP_FPS),Size( cap_I1.get(CV_CAP_PROP_FRAME_WIDTH)*2 ,cap_I1.get(CV_CAP_PROP_FRAME_HEIGHT) ));  // assuming same properties as I1 video


B1.convertTo(B1,CV_32F);
normalize(B1,B1,0,1,NORM_MINMAX);
B2.convertTo(B2,CV_32F);
normalize(B2,B2,0,1,NORM_MINMAX);


int i = 0;
while(cap_I1.get(CV_CAP_PROP_POS_FRAMES) < cap_I1.get(CV_CAP_PROP_FRAME_COUNT))
{
    Mat I1,I2,F;
    cap_I1 >> I1;
    cap_I2 >> I2;

    
    Mat matte = do_difference_matting(I1,I2,B1,B2,F,0);
    
    // wri << F;
    
    string impath("Results/Matte/");
    stringstream convert;
    convert << i;
    impath.append("Matte_");
    impath.append(convert.str());
    impath.append(".jpeg");
    
    string impath2("Results/Foreground/");
    impath2.append("Foreground_");
    impath2.append(convert.str());
    impath2.append(".jpeg");
    
    if( imwrite(impath.data(),matte) != true)
    {
        cout << "\nSome Problem Writing Results! Exiting!! Restart Code again, sorry!\n";
        exit(1);
    }

    if( imwrite(impath2.data(),matte) != true)
    {
        cout << "\nSome Problem Writing Results! Exiting!! Restart Code again, sorry!\n";
        exit(1);
    }
    
i++;    
}



cap_I1.release();
cap_I2.release();
return 1;
}   
