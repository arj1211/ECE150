//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool stringToInt(const char input[], int& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//



/*
  - some cases will include INT_MAX, INT_MAX+1 (overflow), INT_MIN, INTMIN-1 (overflow)
  - program shoult NOT be able to take multiple leading signs
    * 2147483647 should be fine
    * 2147483648 should return false
    * -2147483648 should be fine
    * -2147483649 should return false
  - 

*/







bool stringToInt(const char input[], int& value) {
  // Your code here ...

  int i = 0;
  int negative = 1;
  //bool alreadyHasSign = false;

  if (input==NULL) return false;

  value = 0;
  while (input[i]!=0)
  {
    if ((input[i]=='+' || input[i]=='-') && i!=0) return false;
    if (input[i]=='-' && i==0) 
    {
      negative = -1;
    }
    else if (input[i]=='+' && i==0)
    {
      negative = 1;
    }
    else if (input[i]>='0' && input[i]<='9')
    {
      // check if after appending digit to value, will it overflow
        // if yes, return false
        // if no, append digit to value 

      if (value>214748364 || value<-214748364)
        return false;
      else if (value==214748364 && (input[i]-'0')>7)
        return false;
      else if (value==-214748364 && (input[i]-'0')>8)
        return false;



      value = (10*abs(value) +(input[i]-'0'))*negative;
    }
    else return false;
    i++;
  }
  return true;

}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  int argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <int>" << endl;
    return -1;
  }

  if (stringToInt(argv[1],argv1)) 
    cout << "argv[1] is an int with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not an int." << endl;
  return 0;
}

#endif
