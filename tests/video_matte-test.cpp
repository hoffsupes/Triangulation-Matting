#include <trimat/video_matte_applier.h>

int main()
{
  VideoMatte vmatter = VideoMatte("data/Videos/blue_.mp4","data/Videos/green_.mp4","data/b0.png","data/g0.png");  // using example videos
  vmatter.mattedVideoOutput("data/Foreground", "data/Alpha","data/Videos/final_matte.avi", false,0.01);   // using 0.01 as scale for faster processing
  cout <<"\n\nResults have been written out in final_matte.avi. \n\n";
  return 0;
}
