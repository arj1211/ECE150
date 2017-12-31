//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>


using namespace std;

float NthRoot(const float S, const int N, const float precision);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits.h>) if cannot compute the Nth root of S with
// precision.
//

float NthRoot(const float S, const int N, const float precision) {

  float num = S;
  int root = N;
  float estimate;
  float nan = std::numeric_limits<float>::quiet_NaN();

  if (num < 0 && root%2==0)
    return nan;
  else if (root<2)
    return nan;
  else if (precision <= 0)
    return nan;
  else if (num == 0 || num == 1)
    return num;
  else 
  {
    estimate = num/(1.0*root);

    float expn;
    int i;
    float Rn;
    float calculated_precision = precision+1;   

    while ( calculated_precision > precision)
    {
      i = 0;
      expn = 1;
      while (i<(root-1))
      {
          //cout << "i: " << i << ", root: " << root;
        expn*=estimate;
          //cout << ", expn: " << expn << endl;
        i++;
      }

      estimate = (( (1.0*root-1)/root)*estimate + num/(root*expn));

      Rn=1.0;
      int j = 0;
      while (j<root)
      {
          //cout << "j: " << j ;
        Rn*=estimate;
          //cout << ", Rn: " << Rn << endl;
        j++;
      }

      calculated_precision = ( ( (num-Rn)/num < 0 )? -(num-Rn)/num : (num-Rn)/num );

      //cout << setprecision(15) << fixed << "estimate: " << estimate << ", Rn: " << Rn << ", cp: " << calculated_precision << endl;
    }
  }
  return estimate;
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

  if (argc < 4) {
    cerr << "Error: Usage: " << argv[0] << " <number> <root> <precision>; exiting" << endl;
    return -1;
  }

  float root = NthRoot(atof(argv[1]),atoi(argv[2]),atof(argv[3]));
  if (isNaN(root))
    cerr << "Unable to compute " << argv[2] << "th root of " << argv[1] << " with precision " << argv[3] << endl;
  else
    cout << "Root(" << argv[1] << "," << argv[2] << ") = " << root << endl
  << "(with precision " << argv[3] << ")" << endl; 

  return 0;
}

#endif
