//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iostream>
#include <cfloat>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;


// Sample function for which you need to find the root

float f(const float x) {
  return 3.2*x*x*x - 2.1*x - 23.0;
}

float f1(const float x) {
  return x;
}

float f2(const float x) {
  return x*x;
}

float f3(const float x) {
  return x*x*x*x*x*x*x*x*x;
}

float f4(const float x) {
  return x*x+1;
}

float f5(const float x) {
  return x*x*x*x+9;
}


#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize, int counter);
float bisection(const float left, const float right,
		const float precision, const float minIntervalSize);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//


/*
	so the extra param could be a counter
	"If I call on it 10000 times it stops"

	"yeah, you could try adding another param to the bisection 
	function and see if thats acceptable, then just pass it back and forth"

	"It's also supposed to switch left and right if right is less than left"
	"yeah i figured that one out, just put if statement in the bisection 
	function, and call with right first instead of left if left is larger"

	"so to find if your mid is precise enough does it work to find if midpoint-(int)midpoint <= precision?
	No precision should be
	f(midpoint) <= precision"

	"so wait if thats how you test precision how do you test interval size
	right/left -midpoint?
	I just do abs(right) - abs(left) for positive values
	Opposite for negative"

	"If you do a counter in bisection won't it just reset every time?"
	"you could ampersand it, like &i. apparently that makes the value the same no matter where you are in the code"

	"So make a pointer?
	And when you increase it do you increase the pointer or the address location
	How would the syntax look for that"

	"actually it should work to just make a counter, since you only use the bisection function once initially, then you just recursively call the bisectionhelper function
	so just increment the counter each time before you call it"

*/


const float NaN = std::numeric_limits<float>::quiet_NaN();



float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize, int counter)
{
	
	float midpoint = (right+left)/2; // at a certain point, midpoint will be the root
	
	// when should this function terminate? (aka what are the base cases?)
	// 1. when we've approximated the root to an adequate precision
	if (fabs(f(midpoint))<=precision) return midpoint;
	// 2. when the interval size we have left is within the minIntervalSize
	if (fabs(right-left)<=minIntervalSize) return midpoint;
	// 3. when we're in too deep lol (when we've recursed too many times and will overflow if we recurse any more)
	if (counter >= 10000) return midpoint; // if this works i just pulled a fancy; exothicc maths for 150 labs
	// ^^^^^ prolly wont work, in which case set the upper limit of counter to like E6 maybe
	if (isNaN(f(left)) || isNaN(f(right)))
		return NaN;


	// two cases

	if ( f(left)*f(midpoint) < 0 ) // left half has root
	{
		return bisectionHelper(left, midpoint, precision, minIntervalSize, ++counter);
	}
	else if ( f(right)*f(midpoint) < 0 ) // right half has root
	{
		return bisectionHelper(midpoint, right, precision, minIntervalSize, ++counter);
	}
	else if (f(right)*f(midpoint)*f(left)==0)
		return midpoint;

}

float bisection(const float left, const float right,
		const float precision, const float minIntervalSize) {

	// should take care of all the invalid parameters cases
	// makes sure that bisectionHelper only gets valid params and doesnt have to check

	/*
	what params are invalid?
	- if precision is <= 0, its impossible to achieve
	- if the minIntervalSize <= 0, also impossible to achieve
	- maybe if left > right, we should switch them when calling the helper? 
	*/

	// maybe regulate the precision and minIntervalSize? aka modify them if its gonna mess up the helper
	if (precision<=0)
		return NaN; // if this doesnt work, maybe just use a self-made precision constant and use that as my precision?

	if (minIntervalSize<=0)
		return NaN; // well, can't have an interval size that isn't positive


	// what functions are gonna screw up the calculation? (ex. functions without roots maybe?) 
	// 		how do i account for that?
	//			well you already did, cuz f(left)*f(right)<0 must be true in order to call bisectionHelper

	if (f(left)*f(right)>0)
		return NaN; // cuz theres no root within the interval (or well, IVT can't tell, 
					// and if there are roots, theres a minimum of 2, and will have an odd number of roots)
/*
	if (abs(f(left))<=precision) // left end is approximately a root already
		return left;
	if (abs(f(right))<=precision) // right end is approximately a root already
		return right;
*/
	if (left>right) // switch the two ends if theyre the wrong order
		return NaN;
	/*
	if (f(left)<=precision) 
		return left;
	if (f(right)<=precision) 
		return right;
	*/	


	else
		return bisectionHelper(left, right, precision, minIntervalSize, 0);

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
 	
  cout << "left right precision minIntervalSize: ";
  float a, b, c, d;
  cin >> a >> b >> c >> d;

  cout << "root: " << bisection(a,b,c,d) << endl;

  return 0;
}

#endif
