#include <trimat/video.h>
#include <tgmath.h>
#include <trimat/tester.hpp>

int main()
{
  tester tf;
  Video emptyvideo = Video();
  Video video = Video("data/Videos/nasa.mp4");
  unordered_map<string,string> param = video.get_parameters();
  cout << "The parameters are: \n";
  for (auto para : param)
  {cout << para.first << " " << para.second << endl;}
  // video.set_parameters(param);
  unordered_map<string,string> newp = video.wrap_parameters(floor(stoi(param["width"])/2),floor(stoi(param["height"])/2),stoi(param["codec"]),25);
  video.setWriterToPath("data/Videos/nasa2.avi",newp,true); // openCV only supports AVI
  while(video.frame_pos() < video.total_frames())
  {
    Image frame =  video.get_frame();
    video.write_frame(frame);
  }
  unordered_map<string,string> param2 = video.get_parameters();
  cout << "The parameters are: \n";
  for (auto para : param2)
  {cout << para.first << " " << para.second << endl;}

  tf.TESTER("Check to see if parameters have been written in a case when capture is in use and writer is used on same object,overwriting past values",newp == param2);

  emptyvideo.set_parameters(param);
  unordered_map<string,string> ep = emptyvideo.get_parameters();
  for (auto para : ep)

  tf.TESTER("Check to see if empty non-VideoCapture-initialized object successfully sets parameters",param == ep);

  {cout << para.first << " " << para.second << endl;}
  emptyvideo.setWriterToPath("data/Videos/emptyvideo.avi",newp,true);
  unordered_map<string,string> ep2 = emptyvideo.get_parameters();


  tf.TESTER("Check to see if empty non VideoCapture initialized object, which was initalized through a VideoWriter parameter overwrite, successfully sets parameters or not",newp == ep2);
  for (auto para : ep2)
  {cout << para.first << " " << para.second << endl;}
  video.playback();
  emptyvideo.get_frame();
  return 0;
}
