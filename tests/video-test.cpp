#include <trimat/video.h>
#include <tgmath.h>
#include <trimat/tester.hpp>

int main()
{
  tester tf;
  Video emptyvideo = Video();   // empty Video object
  Video video = Video("data/Videos/nasa.mp4");    // Test video loaded into video object
  unordered_map<string,string> param = video.get_parameters();  // easy getting of parameters
  cout << "The parameters are: \n";
  for (auto para : param)
  {cout << para.first << " " << para.second << endl;}   // cyclethgouh all of them

  unordered_map<string,string> newp = video.wrap_parameters(floor(stoi(param["width"])/2),floor(stoi(param["height"])/2),stoi(param["codec"]),25);  // easy wrapping (creation of parameter object)
  video.setWriterToPath("data/Videos/nasa2.avi",newp,true); // overwriting with new sets of parameters on an object which is already in use and parameters initalized through VideoWriter override
  //
  while(video.frame_pos() < video.total_frames())   // easy reading of video,compare this to reading from VideoCapture out of the box!
  {
    Image frame =  video.get_frame(); // easy get frame
    video.write_frame(frame); // easy write frame
  }
  unordered_map<string,string> param2 = video.get_parameters(); // simple get parameters
  cout << "The parameters are: \n";
  for (auto para : param2)  // display them
  {cout << para.first << " " << para.second << endl;}

  tf.TESTER("Check to see if parameters have been written in a case when VideoCapture is in use and VideoWriter is used on same object, overwriting past values",newp == param2);
  // as mentioned in test label

  emptyvideo.set_parameters(param); // easy set_parameters
  unordered_map<string,string> ep = emptyvideo.get_parameters();
  for (auto para : ep)
  {cout << para.first << " " << para.second << endl;}

  tf.TESTER("Check to see if empty non-VideoCapture-initialized object successfully sets parameters",param == ep);  // as mentioned in test label


  emptyvideo.setWriterToPath("data/Videos/emptyvideo.avi",newp,true); // setWriterToPath on empty Video object, parameters not initalized by VidepCapture but through VideoWriter route
  unordered_map<string,string> ep2 = emptyvideo.get_parameters(); // want to check to see if setWriterToPath actually sets parameters and uses them to initialize VideoWriter or not


  tf.TESTER("Check to see if empty non VideoCapture initialized object, which was initalized through a VideoWriter parameter overwrite, successfully sets parameters or not",newp == ep2); // mentioned in test label
  for (auto para : ep2)
  {cout << para.first << " " << para.second << endl;}
  video.playback(); // playback video, default rate of 25 FPS
  cout << "\n Checking to see if abberant attempt to read from non-initialized VideoCapture will result in exit from program or not. Successful run shoud exit program gracefully after displaying a message in next line. \n";
  emptyvideo.get_frame(); // checking to see if abberant attempt to read from non-existant VideoCapture stream (since we never gave it input path) is accounted for or not
  return 0;
}
