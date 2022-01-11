#include <trimat/video.h>
#include <sstream>

Video::Video()
{
    /**
  construtor, initializes the video class object, frames per second
  width, height and codec values
  inpath and outpath are also done
  captureInUse and writerInUse denote if either or both of capture and writer classes are in use

  input arguments: None
  output arguments: None
  */

  FPS = width = height = codec = 0;
  inpath = string("");
  outpath = string("");
  captureInUse = writerInUse = false;
}

Video::Video(string pathname)
{

  /**
  intializes the Videoobject from scratch

  input arguments:
    - pathname (string): The path to the video file which the Video object needs to be initialized with
  output arguments: None
  */


  captureFromPath(pathname);
}

unordered_map<string,string> Video::get_parameters()
{

  /**
  getter, gets all the paramters in string format in form of a hash table

  input arguments: None
  output arguments:
    - parameters (unordered_map<string,string>): The hashmap containing the various parameters relevant to the Video object as it is in it's current state
  */


  unordered_map<string,string> parameters = wrap_parameters(width,height,codec,FPS);
  return parameters;
}

unordered_map<string,string> Video::wrap_parameters(int nwidth,int nheight,int ncodec,int nFPS)
{

  /**
  wraps parameters into a neat hash table, returns it

  input arguments:
    - nwidth (int,default value=0): The width of the video
    - nheight (int,default value=0): The height of the video
    - ncodec (int,default value=0): The numerical code for the OpenCV FOURCC codec
    - nFPS (int,default value=0): The framerate of the video
  output arguments:
    - parameters (unordered_map<string,string>): The hashmap containing the various parameters relevant to the Video object, from the given input parameters
  */

  unordered_map<string,string> parameters;
  parameters["width"] = to_string(int(nwidth));
  parameters["height"] = to_string(int(nheight));
  parameters["codec"] = to_string(int(ncodec));
  parameters["FPS"] = to_string(nFPS);
  return parameters;
}

void Video::unwrap_parameters(unordered_map<string,string> parameters,int & nwidth,int & nheight,int & ncodec,int & nFPS)
{

  /**
  unwraps parameters from a neat hash table

  input arguments:
    - parameters (unordered_map<string,string>): The hashmap containing the various parameters relevant to the Video object
    - nwidth (int): The width of the video, unwrapped or obtained from the unordered map, passed by reference, hence value returned on processing,
    - nheight (int): The height of the video, unwrapped or obtained from the unordered map, passed by reference, hence value returned on processing,
    - ncodec (int): The numerical code for the OpenCV FOURCC codec, unwrapped or obtained from the unordered map, passed by reference, hence value returned on processing,
    - nFPS (int): The framerate of the video, unwrapped or obtained from the unordered map, passed by reference, hence value returned on processing,
  output arguments: None
  */


  nwidth = stoi(parameters["width"]);
  nheight = stoi(parameters["height"]);
  ncodec = stoi(parameters["codec"]);
  nFPS = stoi(parameters["FPS"]);
}

void Video::captureFromPath(string pathname)
{

  /**
  Reads a video file from a given path and then intializes the video paramter values
  sets captureInUse to false

  input arguments:
    - pathname (string): The path to the video file which the Video object needs to initialize an OpenCV VideoCapture object with
  output arguments: None
  */


  if(captureInUse)    // does not read file if object already in use
  {
    cout << "This Video object is already in use for capture for file "<< inpath <<" please consider using a new object!";
  }
  else
  {

  if(!capture.open(pathname.data()))    // exit if incorrect video file given
  {
    cout << "\n Problem in opening " << pathname << "\n Exiting! \n";
    exit(1);
  }
  FPS = capture.get(CAP_PROP_FPS);    // parameters read
  width = capture.get(CAP_PROP_FRAME_WIDTH);
  height = capture.get(CAP_PROP_FRAME_HEIGHT);
  codec = capture.get(CAP_PROP_FOURCC);
  inpath = pathname;
  captureInUse = true;    // captureInUse set to true as VideoCapture object in use
  }

}

void Video::playback(int playbackFPS)
{

  /**
  plays back video

  input arguments:
    - playbackFPS (int,default value=25): The FPS or video framerate which needs to be set to do a custom playback at that framerate
  output arguments: None
  */


  while(frame_pos() < total_frames())
  {
    Image I = get_frame();
    I.show(playbackFPS);
  }

}

void Video::write_frame(Image I)
{

  /**
  writes a frame to the video

  input arguments:
    - I (Image): Write a frame to a given VideoWriter stream
  output arguments: None
  */


  if(writerInUse)
  {
    Mat img = I.get_image();
    resize(img,img,Size(width,height));
    writer << img;
  }
  else
  {
    cout << "Illegal operation, cannot write to non-existing stream!";
    exit(1);
  }
}

void Video::setWriterToPath(string pathname,unordered_map<string,string> parameters,bool overwrite_paras)
{


  /**
  Writes a video file to a path
  Relies on parameters being there from VideoCapture
  in case using an empty object (no VideoCapture use) then can either use set_parameters beforehand
  or optionally intialize parameters here

  input arguments:
    - pathname (string): The output path of the video which you want to write, i.e. the output path to the location where the VideoWriter object would be used to write frames to
    - parameters (unordered_map<string,string>): The input hashmap containing the various parameters relevant to the Video object
    - overwrite_paras (bool,default value=false): Typically when ever writing a video, expectance would be that the same, type, kind and size of video being read from is what would be written to
                              As this is supposed to be an input / output Video class, typically meant to support one to one per frame processing and then writing of those results
                              If this flag is set, then the parameters used to write the video can be overridden than what is provide by VideoCapture.
  output arguments: None
  */


  if(writerInUse)   // warns you in case you're about to overwrite an existing writer object
  {
    cout << "The writer is already in use for path " << outpath << " please use a new object!";
  }
  else
  {

    if(!captureInUse)   // if capture not in use
    {
      if((width == 0 || height == 0 || FPS == 0) and (overwrite_paras == false))    // but you haven't set parameters beforehand using set_parameters() and havent chosen to overwrite values with provided ones them here either
      {
        cout << "Error! you need to supply paramater values as you have not initialized capture and are attempting to use writer! Exiting!";
        exit(1);
      }
      set_parameters(parameters);   // otherwise set parameter values by those provided here
    }

    if(captureInUse and overwrite_paras)
    {
      set_parameters(parameters);
    }

    if(!writer.open(pathname.data(),codec,FPS,Size(width,height)))
    {
      cout << "\n Problem in opening " << pathname << "\n Exiting! \n";
      exit(1);
    }
    outpath = pathname;
    writerInUse = true; // writer set to true

  }

}

int Video::frame_pos()
{

  /**
  get the frame position of the current frame

  input arguments: None
  output arguments:
    - frame_position (int): The current frameID or frame number (count) of the VideoCapture object, i.e. where it is in reading a video, in terms of posiiton or location
                            How many frames the VideoCapture object has traversed in processing the input video
  */


  return capture.get(CAP_PROP_POS_FRAMES);
}

int Video::total_frames()
{

  /**
  get the total number of frames

  input arguments: None
  output arguments:
    - total_video_frames (int): The complete number of frames in a video, as given by the VideoCapture object for the input video
  */


  return capture.get(CAP_PROP_FRAME_COUNT);
}

Image Video::get_frame()
{
    /**
  grab the current frame from the videostream and return it

  input arguments: None
  output arguments:
    - image_frame (Image): Get a frame from the VideoCapture object for the given input video
  */
  if(captureInUse)
  {
    Mat I;
    capture >> I;
    return Image(I);
  }
  else  // if capture not in use, should not be used to read from an empty stream
  {
    cout << "Illegal operation, cannot read from non-existing stream!";
    exit(1);
  }
}


void Video::set_parameters(unordered_map<string,string> parameters)
{
    /**
  set parameters from those values provided here

  input arguments:
    - parameters (unordered_map<string,string>): The input hashmap containing the various parameters relevant to the Video object used to set the internal state of the Video object
  output arguments: None
  */
unwrap_parameters(parameters,width,height,codec,FPS);
}

Video::~Video()
{  /**
  delete all VideoCapture and VideoWriter objects using OpenCV's release()

  input arguments: None
  output arguments: None
  */
  capture.release();
  writer.release();
}
