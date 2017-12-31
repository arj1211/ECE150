#include <iostream>
#include <cstdlib>


using namespace std;

int main(const int argc, const char* const argv[])
{
	int a;
	int b;
	int lcm;
	int gcd;

	if (argc > 3)
		cerr<<"Warning: Expecting 2 command-line arguments; received more; ignoring extraneous arguments."<<endl;
	if (argc < 3)
	{	
		//cerr << "Error: Insufficient arguments; expecting 2 values." << endl;
		cerr << "Error: Unable to compute GCD and/or LCM because issa blemazzz ting." << endl;
	}
	else
	{
		a = atoi(argv[1]);
		b = atoi(argv[2]);

		if (a<=0 || b<=0)
			cerr << "Error: Unable to compute GCD and/or LCM because you inputted niggative values fam." <<endl;
		else
		{
			gcd = min(a,b);
			while (gcd>0)
			{
				if (a%gcd==0 && b%gcd==0)
				{
					cout << "GCD(" << a << "," << b << ") = " << gcd << endl;
					lcm = gcd;
					gcd=0; 
				}
				gcd--;
			}

			lcm = ((max(a,b))*(min(a,b)/lcm));

			cout << "LCM(" << a << "," << b << ") = " << lcm << endl;
		}
	}
	return 0;
}