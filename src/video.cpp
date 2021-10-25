#include <trimat/video.h>
#include <sstream>

Video::Video()
{
  // construtor, initializes the video class object, frames per second
  // width, height and codec values
  // inpath and outpath are also done
  // captureInUse and writerInUse denote if either or both of capture and writer classes are in use

  FPS = width = height = codec = 0;
  inpath = string("");
  outpath = string("");
  captureInUse = writerInUse = false;
}

Video::Video(string pathname)
{
  // intializes the Videoobject from scratch

  captureFromPath(pathname);
}

unordered_map<string,string> Video::get_parameters()
{
  // getter, gets all the paramters in string format in form of a hash table

  unordered_map<string,string> parameters = wrap_parameters(width,height,codec,FPS);
  return parameters;
}

unordered_map<string,string> Video::wrap_parameters(int nwidth,int nheight,int ncodec,int nFPS)
{
  // wraps parameters into a neat hash table, returns it
  unordered_map<string,string> parameters;
  parameters["width"] = to_string(int(nwidth));
  parameters["height"] = to_string(int(nheight));
  parameters["codec"] = to_string(int(ncodec));
  parameters["FPS"] = to_string(nFPS);
  return parameters;
}

void Video::unwrap_parameters(unordered_map<string,string> parameters,int & nwidth,int & nheight,int & ncodec,int & nFPS)
{
  // unwraps parameters from a neat hash table
  nwidth = stoi(parameters["width"]);
  nheight = stoi(parameters["height"]);
  ncodec = stoi(parameters["codec"]);
  nFPS = stoi(parameters["FPS"]);
}

void Video::captureFromPath(string pathname)
{
  // Reads a video file from a given path and then intializes the video paramter values
  // sets captureInUse to false

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
  // plays back video

  while(frame_pos() < total_frames())
  {
    Image I = get_frame();
    I.show(playbackFPS);
  }

}

void Video::write_frame(Image I)
{
  // writes a frame to the video

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
  // Writes a video file to a path
  // Relies on parameters being there from VideoCapture
  // in case using an empty object (no VideoCapture use) then can either use set_parameters beforehand
  // or optionally intialize parameters here

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
  // get the frame position of the current frame

  return capture.get(CAP_PROP_POS_FRAMES);
}

int Video::total_frames()
{
  // get the total number of frames

  return capture.get(CAP_PROP_FRAME_COUNT);
}

Image Video::get_frame()
{
  // grab the current frame from the videostream and return it

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
  // set parameters from those values provided here

unwrap_parameters(parameters,width,height,codec,FPS);
}

Video::~Video()
{
  // delete all VideoCapture and VideoWriter objects using OpenCV's release()

  capture.release();
  writer.release();
}
