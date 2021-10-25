#include <trimat/video_matte_applier.h>


VideoMatte::VideoMatte(string bluepath,string greenpath,string bluesstillpath,string greenstillpath)
{
  // parametrized construtor, initializes the green and blue videos and the blank background images

  blue_video = Video(bluepath);
  green_video = Video(greenpath);
  bluestill = Image(bluesstillpath);
  greenstill = Image(greenstillpath);
}

void VideoMatte::mattedVideoOutput(string foregroundpath, string maskpath,string videopath, bool video_only,double scale,bool display)
{
  // Takes a blue and green background video and blue and green background still images and mattes the video along with
  // displaying the output if the display flag is set
  // scales the images as required before processing to bring down processing time and for testing or other purposes
  // if video_only flag set then only outputs a video file, otherwise also outputs per frame alpha mask and mattedFrame file as well, will always output video file by default

  int i = 0,flag=1;
  unordered_map<string,string> result_parameters = blue_video.get_parameters();
  result_video.setWriterToPath(videopath,result_parameters,true);
  foregroundpath = utility.sanitize_folder_path(foregroundpath);
  maskpath = utility.sanitize_folder_path(maskpath);


  while(blue_video.frame_pos() < blue_video.total_frames())
  {
    Image blueframe = blue_video.get_frame();
    Image greenframe = green_video.get_frame();

    if(scale != 1.0)
    {
      blueframe.resize_image(scale);
      greenframe.resize_image(scale);
      if(flag)
      {
        bluestill.resize_image(scale);
        greenstill.resize_image(scale);
        flag=0;
      }

    }

    trimatting(blueframe,greenframe,bluestill,greenstill);

    Image mattedFrame = get_matted_image();
    mattedFrame.convert(CV_8UC3,255.0);
    Image frameMask = get_alpha_mask();
    frameMask.convert(CV_8UC1,255.0);

    result_video.write_frame(mattedFrame);

    if(!video_only)
    {
      mattedFrame.write(utility.iterative_name(foregroundpath,i));
      frameMask.write(utility.iterative_name(maskpath,i));
    }

    if(display)
    {
      Mat newmask;
      cvtColor(frameMask.get_image(), newmask, COLOR_GRAY2BGR);
      hconcat(mattedFrame.get_image(),newmask,newmask);
      imshow("Image Matting Results",newmask);
      waitKey(25);
      cout << "\n Frame Number: " << i << "\n";
    }

    i++;

  }
}
