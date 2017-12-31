#include <iostream>
#include <cstdlib>
using namespace std;

int main(const int argc, const char* const argv[])
{
	float velocity = atof(argv[1]);
	float distance = atof(argv[2]);

	cout << "Initial car velocity: " << velocity << " m/s" << endl;
	cout << "Distance to obstacle: " << distance << " m" << endl;
	cout << "Minimum deceleration: " << ( -(velocity*velocity)/(2*distance) ) << " m/s/s" << endl;
	cout << "Maximum stopping time: " << ( -velocity/( -(velocity*velocity)/(2*distance) ) ) << " s" << endl;
	return 0;
}