//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iostream>



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

int range(const int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);
void selection(int dataset[], int size);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  Return -1 if there there are any problems with the dataset.
//

int range(const int dataset[], const int size)
{
  if (size<=0) return -1;
  int d[size];
  for (int i = 0; i < size; ++i)
    d[i]=dataset[i];

  sort(d,size);

  return d[size-1]-d[0];
}
int mode(const int dataset[], const int size, int mode[]) // in here somewhere, 
// error is for 100000+ numbers
{
  if (size<=0) return -1;
  int d[size];
  for (int i = 0; i < size; i++)
    d[i]=dataset[i];
  sort(d,size);


  if (size==1)
  {
    mode[0]=d[0];
    return 1;
  }

  //d's size>=2
  int largestFreq = 1; // counts the number of occurences a number in data must have to be considered a mode
  int numberOfTimesTheCurrentNumberAppears = 1;
  int modeIndex = 0; // index into mode[] . modeIndex+1 is the number of modes thus far
  mode[modeIndex];
  int currNum = d[0];
  for ( int i=1; i<size;i++)
  {

    if ( currNum == d[i] ) {
      // if the next element in d is the same as the previous one, we have a potential mode
      // numberOfTimesTheCurrentNumberAppears is now equal to the number of times this number has occurred
      numberOfTimesTheCurrentNumberAppears++;
    }
    else
    {
      numberOfTimesTheCurrentNumberAppears=1;
      currNum=d[i];
    }
  
    if ( numberOfTimesTheCurrentNumberAppears > largestFreq ){ // found a new mode that replaces the old
      modeIndex=0;
      largestFreq = numberOfTimesTheCurrentNumberAppears;
      mode[modeIndex] = currNum;
    }
  
    else if ( numberOfTimesTheCurrentNumberAppears == largestFreq ) {// found a new additional mode
      modeIndex++;
      mode[modeIndex]=d[i];
    }
  
  }
  
  return modeIndex+1;



  /*
    int freqSize = d[size-1]+1;
    int freq[freqSize]; // segfault right here
    for (int i = 0; i < freqSize; ++i)
      freq[i]=0;
    int largestFrequency=0;
    for (int i = 0; i < size; ++i)
    {
      freq[d[i]]++;
      if (freq[d[i]]>largestFrequency)
        largestFrequency=freq[d[i]];
    }
    // largestFrequency is the number of times a number must occur in order for it to be a mode
    int j=0;
    int numOfModes=0;
    for (int i = 0; i < freqSize; ++i)
    {
      if (freq[i]==largestFrequency) // found a mode
      {
        numOfModes++;
        mode[j]=i;
        j++;
      }
    }
    return numOfModes;
  
  */

}

bool sort(int dataset[], const int size)
{
  selection(dataset,size);
  return true;
}
void selection(int dataset[], int size)
{

  int maxInd = 0;
  int tmp = 0;
  int ind = 0;

  for (ind = maxInd+1; ind < size; ind++)
  {
    if (dataset[ind] > dataset[maxInd])
      maxInd = ind;
  }
  // maxInd is now index of max item in array

  tmp = dataset[size-1];
  dataset[size-1]=dataset[maxInd];
  dataset[maxInd]=tmp;

  // put the max item at end

  if (size>1)
    selection(dataset, --size);
  // we know that the max val is at the end of the array,
  // so we dont care about it anymore. if the array still
  // has more stuff, we gotta do the same process to
  // the front [size-1] of the array
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

  //int a[1000000]; // this segfaults
  // Some test driver code here ....
  //int data[] = {1, -1, 1, -1, 1, -1};
  //int size = 6;

  int data[argc-1];
  int size;

  int i = 1;
  size = argc-1;

  while(i-1<size)
  {
    data[i-1]=atoi(argv[i]);
    i++;
  }

  //change this to however many modes you expect to find
  int modeArray[100]={0};
  int rng = range(data, size);
  int modes = mode(data, size, modeArray);
  cout << "range: " << rng << ", number of Modes: " << modes << ", Modes are this: ";
  for(int i = 0; i<modes;i++){
  	cout<< modeArray[i];
  	if(i<modes-1){
  		cout << ", ";
  	}
  }
  cout<<endl;
  return 0;
}

#endif
