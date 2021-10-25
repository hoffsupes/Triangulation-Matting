#ifndef _TESTER_GUARD_
#define _TESTER_GUARD_

#include <iostream>

//// ///////////////////////////////////////////////////
//// tester class
//// ///////////////////////////////////////////////////
//// Contains a very simple test based utility function
//// ///////////////////////////////////////////////////


using namespace std;

class tester
{
  // contains the method TESTER
  public:
  void TESTER(string testname,bool condition);
};

void tester::TESTER(string testname, bool condition)
{
  // performs a test labeled as testname and sees if it is true
  if(condition == false)
  {
    cout << "\n" << __FUNCTION__ << " failed for test " << testname.data() << "\n";

  }
  else
  {
    cout << "\n" << testname.data() << " successful for function " << __FUNCTION__ << "\n";
  }

}

#endif
