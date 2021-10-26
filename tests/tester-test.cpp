#include <iostream>
#include <trimat/tester.hpp>

int main()
{
tester tf;

tf.TESTER("True condition -- test successful output, SUCCESS IF PASSES",true);  // testing the TESTER
tf.TESTER("False condition -- fail output, SUCCESS IF FAILS",false);
tf.DISPLAY_SUMMARY();

return 0;
}
