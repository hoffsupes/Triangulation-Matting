#include <trimat/video_matte_applier.h>
#include <trimat/matte_applier.h>
#include <stdlib.h>

int main(int argc, char** argv) // main
{
  if(argc < 2)    // wrong number of parameters entered
  {
    cout <<"\n Incorrect number of command line paramters entered!\n";
    exit(1);
  }

  // for (int i=0; i < argc;i++)
  // {
  //   cout << "Parameter : " << i << " is " << argv[i] <<" \n ";
  // }
  string mode = string(argv[1]);
  string bluepath = string(argv[2]);
  string greenpath = string(argv[3]);
  string bluesstillpath = string(argv[4]);
  string greenstillpath = string(argv[5]);
  string foregroundpath = string(argv[6]);
  string alphapath = string(argv[7]); // all parameters read

  if(mode == string("video-matte"))
  {
    string mattedvideopath = string(argv[8]);
    double scale = atof(argv[9]);
    bool video_only = bool(atoi(argv[10]));
    bool display = bool(atoi(argv[11]));    // all parameters read
    VideoMatte vmatter = VideoMatte(bluepath,greenpath,bluesstillpath,greenstillpath); //
    vmatter.mattedVideoOutput(foregroundpath, alphapath,mattedvideopath, video_only,scale,display);   // matted video output
  }
  else if(mode == string("image-matte"))
  {
    Image bluepath_image = Image(bluepath);
    Image greenpath_image = Image(greenpath);
    Image bluesstill_image = Image(bluesstillpath);
    Image greenstill_image = Image(greenstillpath);

    Matte matte = Matte(bluepath_image,greenpath_image,bluesstill_image,greenstill_image); // quick initializations from filenames!
    matte.apply_matte();    // apply matting to blue image, green image, blue and green background only images
    Image mattedImage = matte.get_matted_image(); // get result
    Image alphaMask = matte.get_alpha_mask();   // get mask

    alphaMask.convert(CV_8UC1,255.0); // 8 bit pixel values
    mattedImage.convert(CV_8UC3,255.0); // 8 bit pixel values

    mattedImage.write(foregroundpath);
    alphaMask.write(alphapath); // write them
  }
    else
    {
      cout << "\nPlease enter correct parameters!\n\n\n";
      exit(1);
    }
  return 0;
}
