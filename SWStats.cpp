#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;

int windowSize;

int N;



float SWMin(int winSiz, int currIndex, float data[])
{
	// gives min val from winSiz to currIndex
	float m = data[currIndex];

	for (int i = currIndex-1; i > currIndex-winSiz; --i)
		m = min(m, data[i]);

	return m;

}

float SWMax(int winSiz, int currIndex, float data[])
{
	// gives max val from winSiz to currIndex
	float m = data[currIndex];
	//cout << "initial m: " << m << endl;
	for (int i = currIndex-1; i > currIndex-winSiz; --i)
	{
		m = max(m, data[i]);
		//cout << "m: "<<m<<endl;
	}
	return m;
}

float SWAvg(int winSiz, int currIndex, float data[])
{
	// gives avg from winSiz to currIndex
	float m = data[currIndex];

	for (int i = currIndex-1; i > currIndex-winSiz; --i)
		m += data[i];

	return m/(1.0*winSiz);
}




int main(const int argc, const char* const argv[])
{
	N=argc-2;

	if (N<1)
		cerr << "Error: Insufficient arguments." << endl;
	else
	{
		windowSize = atoi(argv[1]);
		if (windowSize > N || windowSize==1)
			cerr << "Warning: bare window size ahlie." << endl;
		if ( windowSize < 1)
			cerr << "Error: Unable to compute statistics over data set because Window Size cannot be negative." << endl;
		else
		{
			float dataset[N+windowSize];
			

			//N=5
			//input: 3 1 2 3 4 5
			//argv[]:1 2 3 4 5 6
			//wiS=3
			//argv[1]=wiS
			//dataset= {1 1 1 2 3 4 5}
			// index:   0 1 2 3 4 5 6

			int k = 2;
			for (int i = 0; i < windowSize; ++i)
			{
				dataset[i]=atof(argv[k]);
			}
			k++;
			for (int i = windowSize; i < N+windowSize-1; ++i)
			{
				dataset[i]=atof(argv[k]);
				k++;
			}

			cout << "Window Size: " << windowSize << endl;
			cout << "Sample\tValue\tSWMinimum\tSWAverage\tSWMaximum"<<endl;

			for (int i = 1; i <= N; ++i)
			{
				int currIndex = i+windowSize-2;
				cout << i << "\t" << dataset[currIndex] << "\t" << SWMin(windowSize, currIndex, dataset) << "\t" << SWAvg(windowSize, currIndex, dataset) << "\t" << SWMax(windowSize, currIndex, dataset) << endl;

			}


		}
	}
	return 0;
}