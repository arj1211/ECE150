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

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
	        float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

const float INF = std::numeric_limits<float>::infinity();
const float NaN = std::numeric_limits<float>::quiet_NaN();

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
  if (
    minimum(dataset,size)!=NaN  
    && minimum(dataset,size)!=-INF
    && minimum(dataset,size)!=INF

    && average(dataset,size)!=NaN
    && average(dataset,size)!=INF
    && average(dataset,size)!=-INF

    && maximum(dataset,size)!=INF
    && maximum(dataset,size)!=-INF
    && maximum(dataset,size)!=NaN

    && popStdDev(dataset,size)!=INF 
    && popStdDev(dataset,size)!=-INF 
    && popStdDev(dataset,size)!=NaN 

    && smplStdDev(dataset,size)!=INF 
    && smplStdDev(dataset,size)!=-INF 
    && smplStdDev(dataset,size)!=NaN 

    && median(dataset,size)!=INF
    && median(dataset,size)!=-INF
    && median(dataset,size)!=NaN
    )
    {
      min = minimum(dataset,size);
      avg = average(dataset,size);
      max = maximum(dataset,size);
      popSD = popStdDev(dataset,size);
      smplSD = smplStdDev(dataset,size);
      mdn = median(dataset,size);
      return true;
    }
  else
    return false;
}   


float minimum(const float dataset[], const int size) {

  float minn = INF;
  // cout << "~~~~~COMPUTING MIN~~~~~" << endl;
  
  for (int i = 0; i < size; ++i)
  {
    minn=(minn<dataset[i])?minn:dataset[i];
  // cout <<"curr min , dataset val : "<< minn << ", " << dataset[i] << endl;
  }

  // cout << "FINAL MIN: " << minn << "\n~~~~~~~~~~~~~~~~~~~~\n\n"; 
  return minn;

}

float average(const float dataset[], const int size) {
  float sum=0;
  for (int i = 0; i < size; ++i)
  {
    sum+=dataset[i];
  }
  // cout << "\n~~~~~\nSUM: " << sum << "\n~~~~~\n";
  return (sum/(1.0*size));
}

float maximum(const float dataset[], const int size) {
  float maxx = -INF;
  // cout << "~~~~~COMPUTING MAX~~~~~" << endl;
  for (int i = 0; i < size; ++i)
  {
    maxx=(maxx>dataset[i])?maxx:dataset[i];
    // cout <<"curr max , dataset val : "<< maxx << ", " << dataset[i] << endl;
  }

  // cout << "FINAL MAX: " << maxx << "\n~~~~~~~~~~~~~~~~~~~~\n\n"; 
  return maxx;
}

float popStdDev(const float dataset[], const int size) {

  int N = size;
  if ( N <=0 )
    return INF;
  else
  {
    float sumprod = 0;
    float aver = average(dataset, N);
    for (int i = 1; i <= N; ++i)
      sumprod += (dataset[i-1]-aver)*(dataset[i-1]-aver);
    float popD = sqrt(sumprod/(1.0*N));
    return popD;
  }


}

float smplStdDev(const float dataset[], const int size) {

  int N = size;

  if ( N <=1 )
    return INF;
  else
  {
    float sumprod = 0;
    float aver = average(dataset, N);
    for (int i = 1; i <= N; ++i)
      sumprod += (dataset[i-1]-aver)*(dataset[i-1]-aver);
    float sumD = sqrt(sumprod/(1.0*N-1));
    return sumD;
  }

}

float median(const float dataset[], const int size) {
  
  float tmp;
  float data[size];

  for (int i = 0; i < size; ++i)
    data[i]=dataset[i];

  for (int i = 0; i < size; ++i)
  {
    for (int j = i+1; j < size; ++j)
    {
      if (data[i] > data[j])
      {
        tmp = data[i];
        data[i]=data[j];
        data[j]=tmp;
      }
    }
  }

  if (size%2)
    return data[size/2];
  else
  {
    // 0 1 2 3   4 5   6 7 8 9
    return (data[size/2]+data[(size-1)/2])/2;
  }
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
  int size = 310;
  float dataset1[] = {17.6028, 10.9157, 16.7465, 16.9766, 18.6747, 
    7.96327, 10.0283, 16.5234, 9.16662, 13.3095, 12.161, 
    14.4331, 10.4718, 12.701, 19.2834};
    float dataset2[] = {-31.6048864, 2.054792907, 59.86833835, 112.1203167, -86.23859712, -29.08342108, -43.62957942, -4.113551697, -52.10698806, 10.67979805};
    float dataset[]={1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0};
  float min;
  float avg;
  float max;
  float popStDev;
  float smplStDev;
  float median;

  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, median)) {
    cout << "Minimum: " << min << endl
	 << "Average: " << avg << endl
	 << "Median:  " << median << endl
	 << "Maximum: " << max << endl
	 << "Population Standard Deviation: " << popStDev << endl
	 << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif
