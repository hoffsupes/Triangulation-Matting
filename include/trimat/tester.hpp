#ifndef _TESTER_GUARD_
#define _TESTER_GUARD_

#include <iostream>
#include <experimental/source_location>
#include <vector>

//// ///////////////////////////////////////////////////
//// tester class
//// ///////////////////////////////////////////////////
//// Contains a very simple test based utility function
//// ///////////////////////////////////////////////////


using namespace std;
using namespace experimental;

class tester
{
  // contains the method TESTER
  vector<string> fails,successes;
  public:
  void display_summary_helper(string,vector<string>);
  void TESTER(string testname,bool condition, source_location location  = source_location::current());
  void DISPLAY_SUMMARY();
  vector<string> get_fails();
  vector<string> get_successes();
};

vector<string> tester::get_fails()
{
  // getter for fails
  return fails;
}

vector<string> tester::get_successes()
{
  // getter for successes
  return successes;
}

void tester::TESTER(string testname, bool condition, source_location location)
{
  // performs a test labeled as testname and sees if it is true

  if(condition == false)
  {
    cout << "\n \t" << location.function_name() << " --- failed for test " << testname.data() << " on function " << location.function_name() << " in line " << location.line() <<  " in file " << location.file_name() << "\n";
    fails.push_back(" \t \t" + string(location.function_name()) + " --- failed for test " + testname + " on function " + string(location.function_name()) + " in line " + to_string(location.line()) +  " in file " + string(location.file_name()));
  }
  else
  {
    cout << "\n \t" << testname.data() << " --- SUCCESSFUL for function " << location.function_name() << " on line " << location.line() <<  " in file " << location.file_name() << "\n";
    successes.push_back(" \t \t" + testname + " --- SUCCESSFUL for function " + string(location.function_name()) + " on function " + string(location.function_name()) + " in line " + to_string(location.line()) +  " in file " + string(location.file_name()));
  }

}

void tester::display_summary_helper(string case_string,vector<string> fails)
{
  cout << "\n\n\n Number of "<< case_string.data() <<": " << fails.size();
  if(fails.size())
  {
    cout << "\n\n Summary of all test "<< case_string.data() <<":: \n\n";
    for(int i=0; i < fails.size(); i++)
    {
      cout << fails[i].data() << "\n";
    }
  }

}

void tester::DISPLAY_SUMMARY()
{

  // displays summary of errors

  display_summary_helper("FAILURES",fails);
  display_summary_helper("SUCCESSES",successes);

  cout << "\n\n\n";
}

#endif
