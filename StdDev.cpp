#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;



float avg(int n, float arr[])
{

	//cout << "AVG:\n~~~~~~~~~~"<< endl;
	//cout << "n: " << n << endl;
	if ( n <=0 )
		return -FLT_MAX;
	else
	{
		float aver = 0;
		for (int i = 1; i <= n; i++)
		{
			aver+=arr[i];
			//cout << "arr[i]: " << arr[i] << ", aver: " << aver << endl;
		}
		aver= aver/(1.0*n);
		//cout << "\naver: " << aver << "\n~~~~~~~~~~" << endl;
		return aver;
	}
}

float popDev(int N, float data[])
{
	//cout << "POPDEV:\n~~~~~~" << endl;
	//cout << "N: " << N << endl;
	if ( N <=0 )
		return -FLT_MAX;
	else
	{
		float sumprod = 0;
		float aver = avg(N, data);
		for (int i = 1; i <= N; ++i)
			sumprod += (data[i]-aver)*(data[i]-aver);
		float popD = sqrt(sumprod/(1.0*N));
		return popD;
	}
}

float samDev(int N, float data[])
{
	if ( N <=1 )
		return -FLT_MAX;
	else
	{
		float sumprod = 0;
		float aver = avg(N, data);
		for (int i = 1; i <= N; ++i)
			sumprod += (data[i]-aver)*(data[i]-aver);
		float sumD = sqrt(sumprod/(1.0*N-1));
		return sumD;
	}
}

int main(const int argc, const char* const argv[])
{
	
	int N=argc-1;
	float dataset[N];
	float mini = FLT_MAX;
	float maxi = -FLT_MAX;

	if (N<1)
		cerr << "Error: Unable to compute statistics over data set because no data fam, link mans." << endl;
	else
	{

		// input all vals
		for (int i = 1; i <= N; ++i)
		{
			dataset[i]=atof(argv[i]);
			mini = (dataset[i]<mini)? dataset[i]: mini;
			maxi = (dataset[i]>maxi)? dataset[i]: maxi;
		}

		cout << "Number of floating-point numbers: " << N << endl;

		// find min

		cout << "Minimum floating-point number: " << mini << endl;

		// find avg

		cout << "Average floating-point number: " << avg(N, dataset) << endl;

		// find max

		cout << "Maximum floating-point number: " << maxi << endl;

		//pop

		cout << "Population standard deviation: " << popDev(N, dataset) << endl;

		if (N==1)
			cout << "Sample standard deviation: infinity" << endl; 
		else
			cout << "Sample standard deviation: " << samDev(N,dataset) << endl; 
	}
	return 0;
}