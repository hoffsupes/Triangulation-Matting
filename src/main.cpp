#include <trimat/video_matte_applier.h>

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

  string bluepath = string(argv[1]);
  string greenpath = string(argv[2]);
  string bluesstillpath = string(argv[3]);
  string greenstillpath = string(argv[4]);
  string foregroundpath = string(argv[5]);
  string alphapath = string(argv[6]);
  string mattedvideopath = string(argv[7]);
  double scale = stod(argv[8]);
  bool video_only = bool(stoi(argv[9]));
  bool display = bool(stoi(argv[10]));    // all parameters read

  VideoMatte vmatter = VideoMatte(bluepath,greenpath,bluesstillpath,greenstillpath); //
  vmatter.mattedVideoOutput(foregroundpath, alphapath,mattedvideopath, video_only,scale,display);   // matted video output
  return 0;
}
