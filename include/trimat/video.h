#ifndef _VIDEO_GUARD_
#define _VIDEO_GUARD_

#include <trimat/image.h>
#include <unordered_map>
#include <stdlib.h>

//// ///////////////////////////////////////////////////
//// Video class
//// ///////////////////////////////////////////////////
//// Contains capability of both the VideoWriter and
//// the VideoCapture objects in OpenCV, puts them together
//// and makes it possible to use them together if needed be
//// also contains various parameters needed to use them
//// and to also capabilities to easily set and get parameters
//// with great ease and in batch
//// By default VideoCapture will overwrite values on reading
//// a video and expectance is that VideoWriter will use same
//// properties to write, unless the user specifies parameters
//// and requirement to overwrite them and this option has been
//// provided to them (if they choose to do so). Typically you would
//// write with the same codec,FPS, width and height of the videos
//// hence I thought it would be useful to have that capability here
//// but the opposing avenue (providing ones own parameters)
//// has also been given.
//// ///////////////////////////////////////////////////


class Video
{
  VideoCapture capture;   // for opening a video
  VideoWriter writer;   // for writing a video
  int codec = 0;   // the codec for the video
  int FPS = 0;   // frames per second
  int width = 0;   // width
  int height = 0;   // height
  string inpath;   // inputpath of video to be read
  string outpath;   // outputpath of the video to be written
  bool captureInUse = false;   // is the object being used to open a video file?
  bool writerInUse = false;      // is the writer being used to write to a file

public:
  Video();   // Video default constructor
  Video(string pathname);   // parameterized constructor
  ~Video();   // destructor to cleanly remove the capture and writer objects
  unordered_map<string,string> get_parameters();   // get the parameters for capture object
  void set_parameters(unordered_map<string,string>);   // set the parameters as per the given object
  void write_frame(Image);   // write a frame to a path
  void captureFromPath(string);   // videocapture object initialized from a path, all parameters initialized as per this
  void setWriterToPath(string pathname,unordered_map<string,string> paramters,bool overwrite_capture=false);   // videowriter writes to a path, uses the parameters from capture or provided by user
  int frame_pos();   // frame position when reading a video, for video capture (reading)
  int total_frames();   // total number of frames, for video capture
  Image get_frame();   // get a frame as an image, for video capture
  void playback(int playbackFPS=25);   // play a video at framerate of 25 frames per second
  unordered_map<string,string> wrap_parameters(int nwidth,int nheight,int ncodec,int nFPS); // wraps parameters into a hash table
  void unwrap_parameters(unordered_map<string,string> parameters, int & nwidth,int & nheight,int & ncodec,int & nFPS); // unwraps parameters from a hash table


};

#endif
