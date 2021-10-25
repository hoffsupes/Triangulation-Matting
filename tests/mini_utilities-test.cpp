#include <trimat/mini_utilities.hpp>
#include <trimat/tester.hpp>

int main()
{
tester tf;

miniUtilities utility;

tf.TESTER("iterative_name test",utility.iterative_name("foreground",10,".jpeg") == string("foreground/10.jpeg"));
tf.TESTER("iterative_name test",utility.iterative_name("foreground",10,".png") == string("foreground/10.png"));
tf.TESTER("iterative_name test",utility.iterative_name("background",15,".bmp") == string("background/15.bmp"));
tf.TESTER("iterative_name test",utility.iterative_name("background",18,".jpeg") == string("background/18.jpeg"));

tf.TESTER("sanitize_folder_path test",utility.sanitize_folder_path("foreground/") == string("foreground"));
tf.TESTER("sanitize_folder_path test",utility.sanitize_folder_path("background/") == string("background"));
tf.TESTER("sanitize_folder_path test",utility.sanitize_folder_path("alpha/") == string("alpha"));

return 0;
}
