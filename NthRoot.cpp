#include <iostream>
#include <cstdlib>
#include <iomanip>


using namespace std;

int main(const int argc, const char* const argv[])
{

	float num;
	int root;
	float precision;
	float estimate;

	if (argc > 4)
		cerr << "Warning: Expecting 3 command-line arguments; received more; ignoring extraneous arguments." << endl;
	if (argc < 4)
	{	
		cerr << "Error: Unable to compute Nth root because issa blemazzz ting." << endl;
	}
	else
	{
		num = atof(argv[1]);
		root = atoi(argv[2]); // error check int/float if needed
		precision = atof(argv[3]);

		/*
			What are all possible errors?
			- num<0 && root%2==0
			- root not an integer 
			- root<2
			- num==0 (div by 0)
			- precision < 0
		*/

		if (num < 0 && root%2==0)
			cerr << "Error: Unable to compute Nth root because issa blemazzz ting." << endl;
		else if (atof(argv[2])!=root)
			cerr << "Error: Unable to compute Nth root because issa blemazzz ting." << endl;
		else if (root<2)
			cerr << "Error: Unable to compute Nth root because issa blemazzz ting." << endl;
		else if (precision < 0)
			cerr << "Error: Unable to compute Nth root because issa blemazzz ting." << endl;
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
					cout << ", expn: " << expn << endl;
					i++;
				}

				estimate = (( (1.0*root-1)/root)*estimate + num/(root*expn));

				Rn=1.0;
				int j = 0;
				while (j<root)
				{
					//cout << "j: " << j ;
					Rn*=estimate;
					cout << ", Rn: " << Rn << endl;
					j++;
				}

				calculated_precision = ( ( (num-Rn)/num < 0 )? -(num-Rn)/num : (num-Rn)/num );

			//cout << setprecision(15) << fixed << "estimate: " << estimate << ", Rn: " << Rn << ", cp: " << calculated_precision << endl;
			}

			cout << "Root(" << num << ", " << root << ") = " << estimate << "\n(with precision " << calculated_precision << ")" << endl;
		}
	}
	return 0;
}