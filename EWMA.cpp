#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;

int main(const int argc, const char* const argv[])
{
	float alpha; 
	int ageLim; 
	int sample = 1;
	float mmin = FLT_MAX;
	float mmax = FLT_MIN;
	float avg;
	int counter;
	float val;


	if (argc < 4)
		cerr << "Error: Insufficient arguments; expecting at least 4 arguments." << endl;
	else if (atof(argv[1]) > 1 || atof(argv[1]) < 0)
		cerr << "Error: Alpha value must be between 0 and 1 inclusive." << endl;
	else if (atoi(argv[2])<=0 || abs(atoi(argv[2])-atof(argv[2]))>0.0001)
		cerr<<"Error: Age limit must be a positive integer value"<<endl;
	else
	{
		alpha = atof(argv[1]);
		ageLim = atoi(argv[2]);
		avg = atof(argv[3]); // initialize average to first sample
		
		cout << "Sample\tValue\tMinimum\tEWMA\tMaximum" << endl;

		int ind_min; // index of the latest min val
		int ind_max; // index of the latest max val
		int curr_ind; // current index into argv

		counter = argc - 3;
		while (counter)
		{
			curr_ind = sample + 2;
			val = atof(argv[curr_ind]);

			if (val < mmin || (ind_min <= (curr_ind - ageLim)) )
			{
				mmin = val;
				ind_min = curr_ind;
			}
			
			if (val > mmax || (ind_max <= (curr_ind - ageLim)))
			{
				mmax = val;
				ind_max = curr_ind;
			}


			avg = (alpha * val + (1 - alpha) * avg);

			cout << sample << "\t" << val << "\t" << mmin << "\t" << avg << "\t" << mmax << endl;


			sample++;
			counter--;
		}


	}

}