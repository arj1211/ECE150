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

int SWStats(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& min, float& avg, float& max, float& smplSD, float& mdn);

int SWMinimum(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& minimum);
int SWAverage(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& average);
int SWMaximum(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& maximum);
int SWSmplStdDev(const float dataset[], const int size, const int currentSample,
    const int windowSize, float& smplStdDev);
int SWMedian(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& median);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//


#define d(x) if(DEBUGON) {cout << #x << ": " << x << endl;}
#define p(y) if(DEBUGON) {cout << y << endl;}
#define brk if(DEBUGON) {cout << "~~~~~~~~~~" << endl;}
#define DEBUGON 1
const float INF = std::numeric_limits<float>::infinity();
const float NaN = std::numeric_limits<float>::quiet_NaN();

int SWStats(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& min, float& avg, float& max, float& smplSD, float& mdn)
{

    if (size < 1)
    	return -1;
    if (windowSize < 1)
        return -2;

    // newIndex = oldIndex + windowSize - 1;


    //size=2 currS=0 winS=4


    int newIndex = currentSample+windowSize-1;
    int newSize = size+windowSize-1;
    float data[newSize];


    int datasetAccessIndex = 0;
    // if winSize is 4, elements at 0 1 2 3 should be dataset[0]
    for (int i = 0; i < windowSize; ++i)
	{
		data[i]=dataset[datasetAccessIndex];
	}
	
	datasetAccessIndex++;
    for (int i = windowSize; i < newSize; ++i)
	{
		data[i]=dataset[datasetAccessIndex];
		datasetAccessIndex++;
	}
	


//DEBUGGING CODE (WORKS) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// brk cout << "data: "; 
	// for (int i = 0; i < newSize; ++i)
	// {
	// 	cout <<data[i]<<"  ";
	// }
	// cout << endl;
	// brk
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    SWSmplStdDev(data, size, newIndex, windowSize, smplSD);
    
    if (isinf(smplSD))
       	return -3;

    SWMinimum(data, size, newIndex, windowSize, min);
    SWMaximum(data, size, newIndex, windowSize, max);
    SWAverage(data, size, newIndex, windowSize, avg);
    SWMedian(data, size, newIndex, windowSize, mdn);

    if (windowSize > size || windowSize == 1)
        return 1;
    else
        return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END~OF~SWStats~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// MINIMUM WORKS
int SWMinimum(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& minimum)
{
    float m = INF;
    
    int upperIndex = currentSample;
    int lowerIndex = upperIndex-windowSize+1;

    //d(upperIndex) d(lowerIndex)

    for (int i = upperIndex; i >= lowerIndex; --i)
    {
    	m = (m < dataset[i]) ? m : dataset[i];
    	//d(m)
    }
    minimum = m;
    return 0;
}

// AVERAGE WORKS
int SWAverage(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& average)
{
	float a = 0;

	int upperIndex = currentSample;
    int lowerIndex = upperIndex-windowSize+1;

    for (int i = upperIndex; i >= lowerIndex; --i)
    {
    	a += dataset[i];
    }

    average=(a/(1.0*windowSize));
    return 0;
}


// MAXIMUM WORKS
int SWMaximum(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& maximum)
{
	//brk brk
	float m = -INF;
    
    int upperIndex = currentSample;
    int lowerIndex = upperIndex-windowSize+1;

    //d(m) d(upperIndex) d(lowerIndex)

    for (int i = upperIndex; i >= lowerIndex; --i)
    {
    	m = (m > dataset[i]) ? m : dataset[i];
    	//d(m)
		//d(dataset[i])
    }
    maximum = m;
    //brk brk
    return 0;
}

// finally works, damn
int SWSmplStdDev(const float dataset[], const int size, const int currentSample,
    const int windowSize, float& smplStdDev)
{
    if (windowSize<=1) return INF;

    float s = 0;
    
    int upperIndex = currentSample;
    int lowerIndex = upperIndex-windowSize+1;

    float avg = 0;
    SWAverage(dataset, size, currentSample, windowSize, avg);

    for (int i = upperIndex; i >= lowerIndex; --i)
    {
    	s += (dataset[i]-avg)*(dataset[i]-avg);
    }
    smplStdDev = sqrt(s/(windowSize-1));

    return 0;
}

// MEDIAN WORKS (i think)
int SWMedian(const float dataset[], const int size, const int currentSample, const int windowSize,
    float& median)
{
    float tmp;
    float data[windowSize];

	int upperIndex = currentSample;
    int lowerIndex = upperIndex-windowSize+1;

    int datasetIncrement=lowerIndex;
    for (int i = 0; i < windowSize; ++i)
    {
    	data[i] = dataset[datasetIncrement];
    	datasetIncrement++;
    }


 //    brk cout << "data (median fn): "; 
 //    for (int i = 0; i < windowSize; ++i)
	// {
	// 	cout <<data[i]<<"  ";
	// }
	// cout << endl; brk

    for (int i = 0; i < windowSize; ++i)
    {
        for (int j = i + 1; j < windowSize; ++j)
        {
            if (data[i] > data[j])
            {
                tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
    }

    if (windowSize % 2)
        median = data[windowSize / 2];
    else
        median = (data[windowSize / 2] + data[(windowSize - 1) / 2]) / 2;


    return 0;
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

int main(const int argc, const char* const argv[])
{
    int size = 13;
    float dataset1[] = { 1, 2, 3, 4, 5 };
    float dataset3[] = {17.6028, 10.9157};

    float dataset[]={89,76,56,60,56,78,54,56,77,65,65,45,46};
    
    int windowSize = 4;
    int currentSample = 0;
    float min;
    float avg;
    float max;
    float smplSD;
    float median;

    cout << "Sample \t Minimum \t Average \t Maximum \t Median \t Sample "
            "Standard Deviation"
         << endl;

    while (currentSample < size)
    {
        int retCode
            = SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, median);
        if (retCode >= 0)
        {
            cout << currentSample << "\t " << min << "\t " << avg << "\t " << max << "\t " << median
                 << "\t " << smplSD << endl;
            if (retCode > 0)
                cerr << "Warning: something weird happened, but we computed stats "
                        "anyway ... YMMV"
                     << endl;
        }
        else
        {
            cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
            return (-1);
        }
        ++currentSample;
    }
    return 0;
}

#endif
