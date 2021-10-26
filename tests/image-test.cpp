#include <trimat/image.h>
#include <trimat/tester.hpp>

int main() {
tester tf;
Image frame = Image("data/b0.png"); // intialize an image from a file
frame.assign_name("Test Image");  // name an image
frame.convert(CV_32F);  // convert to float 32 bit
frame.normalize_image(0,1,NORM_MINMAX); // normalize image using a minmax method
cout << "Using get_name : " << frame.get_name() << "\n using show_name \n\n"; // using get_name

tf.TESTER("get_name image test",frame.get_name() == string("Test Image"));  // testing to see if get_name works
Mat image = frame.get_image();    // get Mat object
frame.show_name();    // show name
frame.resize_image(0.5);  // resze easily by scaling
frame.convert(CV_8U); // convert to 8 bit pixel values
Mat image_frame = frame.get_image();

Size ifsize = image_frame.size();
Size isize = image.size();

tf.TESTER("resize_image test",(ifsize.height == isize.height/2) and (ifsize.width == isize.width/2));

frame.write("data/b0_test_write.png");

Image newframe = Image("data/b0_test_write.png");

Mat image_newframe = newframe.get_image();
Mat xord;
bitwise_xor(image_frame,image_newframe,xord);

Mat ch1[3];
split(xord,ch1);
tf.TESTER("image write test", countNonZero(ch1[1]+ch1[0]+ch1[2]) == 0);

Image frameNew = Image(image);
frame.assign_name("show() test");
frame.show(0);
return 0;
}
