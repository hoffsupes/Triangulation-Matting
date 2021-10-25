#include <trimat/image.h>
#include <trimat/tester.hpp>

int main() {
tester tf;
Image frame = Image("data/b0.png");
frame.assign_name("Test Image");
frame.convert(CV_32F);
frame.normalize_image(0,1,NORM_MINMAX);
cout << "Using get_name : " << frame.get_name() << "\n using show_name \n\n";

tf.TESTER("get_name image test",frame.get_name() == string("Test Image"));
Mat image = frame.get_image();
frame.show_name();
frame.resize_image(0.5);
frame.write("data/b0_test_write.png");
frame.show(0);

Image frameNew = Image(image);
return 0;
}
