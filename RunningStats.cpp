#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>

using namespace std;

int main(const int argc, const char* const argv[])
{

	int sample = 1;
	float mmin = FLT_MAX;
	float mmax = FLT_MIN;
	float sum = 0;
	float val;


	if (argc <= 1)
		cerr << "Unable to compute running statistics over data set because no values were provided to the program." << endl;
	else
	{
		cout << "Sample\tValue\tMinimum\tAverage\tMaximum" << endl;

		int count = argc-1;

		while (count)
		{

			val = atof(argv[sample]);

			if (val < mmin)
				mmin = val;
			if (val > mmax)
				mmax = val;

			sum += val;

			cout << sample << "\t" << val << "\t" << mmin << "\t" << (sum / sample) << "\t" << mmax << endl;

			sample++;
			count--;
		}
	}
	return 0;
}