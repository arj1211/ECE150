//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int greatestCommonDenominator(const int, const int);
int leastCommonMultiple(const int, const int);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//

int greatestCommonDenominator(const int a, const int b) {
  if (a<=0 || b<=0)
      return -1;
  int gcd = (a<b)?a:b;
  while (gcd>0)
  {
    if (a%gcd==0 && b%gcd==0)
      return gcd;
    gcd--;
  }

}
int leastCommonMultiple (const int a, const int b) {
  if (a<=0 || b<=0)
      return -1;

  /*
  if (( ((a>b)?a:b) * ( ((a<b)?a:b) /greatestCommonDenominator(a,b))) < a || ( ((a>b)?a:b) * ( ((a<b)?a:b) /greatestCommonDenominator(a,b))) < b)
      return -2;
  */

    if (a==b) return a;



  int maxint = 2147483647;

  int currsum = 0;

  int gcdused = greatestCommonDenominator(a,b);


  // a = 2e6
  // b = 2e6+e5

  int denout = 1000;

  //cout << "a/gcdused : " << a/gcdused << endl;

  for (int i = 0; i < b-1; i++)
  {
    currsum += a/gcdused;

    // if (!i%denout) 
    //   cout << "currsum: " << currsum << endl;

    if (currsum > (maxint - a/gcdused))
    {
      
      //cout << "currsum: " << currsum << ", i: " << i << endl;
      //cout << "gonna overflow, returning -2 ..." << endl;
      return -2;
    }
  }

  return ( ((a>b)?a:b) * ( ((a<b)?a:b) /greatestCommonDenominator(a,b))) ;
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

int main(const int argc, const char* const argv[]) {

  //cout << "int max: " << INT_MAX << endl << endl;

  if (argc < 3) {
    cerr << "Error: Usage: " << argv[0] << "<num1> <num2>; exiting" << endl;
    return -1;
  }

  int gcd = greatestCommonDenominator(atoi(argv[1]),atoi(argv[2]));
  if (gcd < 0)
    cerr << "Unable to compute GCD(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "GCD(" << argv[1] << "," << argv[2] << ") = " << gcd << endl;

  int lcm = leastCommonMultiple(atoi(argv[1]),atoi(argv[2]));
  if (lcm < 0)
    cerr << "Unable to compute LCM(" << argv[1] << "," << argv[2] << ")" << endl;
  else
    cout << "LCM(" << argv[1] << "," << argv[2] << ") = " << lcm << endl;


  return 0;
}

#endif
