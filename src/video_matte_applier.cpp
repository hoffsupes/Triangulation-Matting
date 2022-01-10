#include <trimat/video_matte_applier.h>


VideoMatte::VideoMatte(string bluepath,string greenpath,string bluesstillpath,string greenstillpath)
{
  // parametrized construtor, initializes the green and blue videos and the blank background images
  //
  // input arguments:
  //   - bluepath (string): The path to the video containing the foreground on blue background
  //   - greenpath (string): The path to the video containing the foreground on green background
  //   - bluestillpath (string): The path to the image containing the blank blue background
  //   - greenstillpath (string): The path to the image containing the blank green background
  // output arguments: None

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
  //
  // input arguments:
  //   - foregroundpath (string): The path to the foler where the foregrounds from per frame processing are saved as images, only if video_only flag is not set
  //   - maskpath (string): The path to the folder where to save the per frame alphamatte as images, only if video_only flag is not set
  //   - videopath (string): The path to the output video of foregrounds from per frame processing
  //   - video_only (bool,default value=true): The flag which if set only outputs the foreground video to videopath, if not set, also additionally outputs the per frame alphamatte and foreground images to the respective maskpath and foregroundpath folders
  //   - scale (double,default value=1.0): The scaling factor by which all input must be scaled to before doing any matting, for testing purposes
  //   - display (bool,default value=true): The flag if set, diplays the foreground and alphamatte as the per frame processing is happening
  // output arguments: None

  int i = 0,flag=1;
  unordered_map<string,string> result_parameters = blue_video.get_parameters(); // get parameters from blue_video to initialize results_video
  result_video.setWriterToPath(videopath,result_parameters,true); // use them to actually intialize results video


  while(blue_video.frame_pos() < blue_video.total_frames()) // easy read of videos
  {
    Image blueframe = blue_video.get_frame();
    Image greenframe = green_video.get_frame(); // get frames

    if(scale != 1.0)    // scale is not one, if it is, don't needlessly call resize
    {
      blueframe.resize_image(scale);
      greenframe.resize_image(scale);
      if(flag)        // don't keep resizing blank images over and over again
      {
        bluestill.resize_image(scale);
        greenstill.resize_image(scale);
        flag=0;
      }

    }

    trimatting(blueframe,greenframe,bluestill,greenstill);    // call the trimatting function

    Image mattedFrame = get_matted_image();
    mattedFrame.convert(CV_8UC3,255.0);
    Image frameMask = get_alpha_mask();
    frameMask.convert(CV_8UC1,255.0);     // type conversions for results

    result_video.write_frame(mattedFrame);      // write video, always

    if(!video_only)                               // only video output?
    {
      mattedFrame.write(utility.iterative_name(foregroundpath,i));
      frameMask.write(utility.iterative_name(maskpath,i));      // write Results
    }

    if(display)                                 // display the output if flag set
    {
      Mat newmask;
      cvtColor(frameMask.get_image(), newmask, COLOR_GRAY2BGR); // to concatentate results, need to be 3 layer repeated values
      hconcat(mattedFrame.get_image(),newmask,newmask);   // get new concatenated frame
      imshow("Image Matting Results",newmask);
      waitKey(25);                                            // waits for 25 ms before proceeding
      if(i%100 == 0)    // display count per 100 iterations
      {cout << "\n Frame Number: " << i << "\n";}
    }

    i++;

  }
}
