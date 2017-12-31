#include <iostream>
#include <cstdlib>
using namespace std;

int main(const int argc, const char* const argv[])
{
	int P = atoi(argv[1]);
	int Q = atoi(argv[2]);

	cout << "P: " << P << endl;
	cout << "Q: " << Q << endl;
	cout << "P AND Q: " << (P&&Q) << endl;
	cout << "P OR Q: " << (P||Q) << endl;
	cout << "NOT P: " << (!P) << endl;
	cout << "NOT Q: " << (!Q) << endl;


	return 0;
}