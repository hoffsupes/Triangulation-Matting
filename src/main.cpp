#include <trimat/video_matte_applier.h>
#include <trimat/matte_applier.h>

int main(int argc, char** argv) // main
{
  if((argc < 2) and (argc != 5))    // wrong number of parameters entered
  {
    cout <<"\n Incorrect number of command line paramters entered!\n";
    exit(1);
  }

  for (int i=0; i < argc;i++)
  {
    cout << "Parameter : " << i << " is " << argv[i] <<" \n ";
  }
  string mode = string(argv[1]);
  string bluepath = string(argv[2]);
  string greenpath = string(argv[3]);
  string bluesstillpath = string(argv[4]);
  string greenstillpath = string(argv[5]);
  string foregroundpath = string(argv[6]);
  string alphapath = string(argv[7]);
  string mattedvideopath = string(argv[8]);
  double scale = stod(argv[9]);
  bool video_only = bool(stoi(argv[10]));
  bool display = bool(stoi(argv[11]));    // all parameters read

  if(mode.data() == "video-matte")
  {
    VideoMatte vmatter = VideoMatte(bluepath,greenpath,bluesstillpath,greenstillpath); //
    vmatter.mattedVideoOutput(foregroundpath, alphapath,mattedvideopath, video_only,scale,display);   // matted video output
  }
  elif(mode.data() == "image-matte")
  {
    Image bluepath_image = Image(bluepath);
    Image greenpath_image = Image(greenpath);
    Image bluesstill_image = Image(bluesstillpath);
    Image greenstill_image = Image(greenstillpath);

    Matte matte = Matte(bluepath_image,greenpath_image,bluesstill_image,greenstill_image); // quick initializations from filenames!
    matte.apply_matte();    // apply matting to blue image, green image, blue and green background only images
    Image mattedImage = matte.get_matted_image(); // get result
    Image alphaMask = matte.get_alpha_mask();   // get mask

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
