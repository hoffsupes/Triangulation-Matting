#include <trimat/video.h>
#include <tgmath.h>

int main()
{
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
  emptyvideo.set_parameters(param);
  unordered_map<string,string> ep = emptyvideo.get_parameters();
  for (auto para : ep)
  {cout << para.first << " " << para.second << endl;}
  emptyvideo.setWriterToPath("data/Videos/emptyvideo.avi",newp,true);
  unordered_map<string,string> ep2 = emptyvideo.get_parameters();
  for (auto para : ep2)
  {cout << para.first << " " << para.second << endl;}
  video.playback();
  emptyvideo.get_frame();
  return 0;
}
