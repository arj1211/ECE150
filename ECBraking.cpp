#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(const int argc, const char* const argv[])
{
	float velo;
	float dist;
	float dec;
	float acc;
	float time;
	float vf;


	//Error messages
	if (argc > 4)
		cerr<<"Warning: Expecting three command-line arguments; received 4; ignoring extraneous arguments."<<endl;
	if (argc < 4)
	{	
		cerr << "Error: Insufficient arguments; expecting 3 values." << endl;
	}
	else	
	{
		velo = atof(argv[1]);
		dist = atof(argv[2]);
		dec = atof(argv[3]);
		dec = -dec;


		//No crash
		if (velo*dist < 0)
			cout<<"There is no possibility of collision because the car is moving away from the obstacle."<<endl;
		// at this point, velo and dist are same direction, so the car (if moving) is going towards obstacle
		else if (velo == 0)
			cout<<"There is no possibility of collision because the car is not moving."<<endl;

		//Certain crash
		else if (dist == 0)
			cout << "Crash will occur in 0 seconds at velocity " << velo << " m/s; deploying airbags."<<endl;
		else if (dec == 0)
			cout << "Crash will occur in "<< dist/velo <<" seconds at velocity " << velo << " m/s; deploying airbags."<<endl;
		//-------------

		else // theres a deceleration, may or may not crash
		{
			// velo nor dist are == 0
			// dist = abs(dist);
			acc=-(velo*velo)/(2*dist); // acc!=0

			if (abs(acc) < abs(dec)) // will not crash
			{
				//time = abs((-velo/(-(velo*velo)/(2*dist))));
				time = (-velo)/acc;
				cout << "Initial car velocity: " << velo << " m/s" << endl;
				cout << "Distance to obstacle: " << dist << " m" << endl;
				cout << "Minimum deceleration: " << abs(acc) << " m/s/s" << endl;
				cout << "Maximum stopping time: " << abs(time) << " s" << endl;

				//cout<<"** acc = "<<acc<<endl;
			}
			
			else if (abs(acc) >= abs(dec)) // will crash
			{
				//check the physics
				vf=sqrt((velo*velo)+2*dec*abs(dist)); /// * problem in this line

				time = (vf-abs(velo))/dec;
				cout << "Crash will occur in " << abs(time) << " seconds at velocity "<< vf*(dist/abs(dist)) <<" m/s; deploying airbags."<<endl;
				
				//cout<<"** acc = "<<acc<<", vf: "<<vf<<endl;
			}
		}
	}
	return 0;
}