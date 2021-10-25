#include <iostream>
#include <trimat/tester.hpp>

int main()
{
tester tf;

tf.TESTER("True condition -- test successful output, SUCCESS IF PASSES",true);
tf.TESTER("False condition -- fail output, SUCCESS IF FAILS",false);

return 0;
}
