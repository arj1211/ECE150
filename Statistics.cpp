#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>

using namespace std;

int main(const int argc, const char* const argv[])
{

	float mmin = FLT_MAX;
	float mmax = FLT_MIN;
	float avg = 0;

	int i = (argc-1);
	int j = 1;

	if (argc == 1)
	{
		cerr << "Unable to compute statistics over data set because no values were provided to the program." << endl;
	}
	else
	{
		while(i > 0)
		{
			avg = (avg + atof(argv[j]));
			if (mmin > atof(argv[j]))
			{
				mmin = atof(argv[j]);
			}
			if (mmax < atof(argv[j]))
			{
				mmax = atof(argv[j]);
			}
			j++;
			i--;
		}
		
		avg = (avg / (argc-1));
		
		cout << "Number of floating-point numbers: " << (argc-1) << endl;
		cout << "Minimum floating-point number: " << mmin << endl;
		cout << "Average floating-point number: " << avg << endl;
		cout << "Maximum floating-point number: " << mmax << endl;
	}
	return 0;
}