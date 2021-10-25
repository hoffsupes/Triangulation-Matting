#ifndef _VIDEO_MATTE_GUARD_
#define _VIDEO_MATTE_GUARD_

#include <trimat/video.h>
#include <trimat/matte_applier.h>
#include <trimat/mini_utilities.hpp>


//// ///////////////////////////////////////////////////
//// VideoMatte class
//// ///////////////////////////////////////////////////
//// Extends and inherits Matte class publicly
//// Is primarily extension of the Matte class to handle video data
//// Mattes each frame of the video and has capability to show end video or save individual frames or even save the video
//// ///////////////////////////////////////////////////

class VideoMatte : public Matte
{
  Video blue_video,green_video,result_video;   // the Video class objects for green,blue and result videos or images where objects are captured with these background colors
  Image bluestill,greenstill;   // blue and green still blank (background only) images
  miniUtilities utility;

public:
  VideoMatte(string,string,string,string);   // parameterized constructor
  void mattedVideoOutput(string foregroundpath, string maskpath,string videopath, bool video_only=true,double scale=1.0,bool display=true);    // given blue and green videos, apply
};                                                                                                                                             // matting to each and every frame
                                                                                                                                              // as per the still images
                                                                                                                                              // optional paramters to store per frames
                                                                                                                                              // mask and matted images as single files
                                                                                                                                              // and option to scale images
                                                                                                                                              // for faster processing if needed be
                                                                                                                                              // e.g. for testing


#endif
