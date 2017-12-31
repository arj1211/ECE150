#include <iostream>
#include <cstdlib>
#include <climits>
#include <cfloat>


using namespace std;

int main(const int argc, const char* const argv[])
{
	int x;
	unsigned int y;
	signed char a;
	short b;
	long c;
	long long d;
	unsigned char e;
	unsigned short f;
	unsigned long g;
	unsigned long long h;
	float i;
	double j;
	long double k;
	
	
	
	x = atoi(argv[1]);
	y = x;
	
	cout << "The value of x is " << x << endl;
	cout << "The value of y is " << y << endl;
	
	
	
	cout << "The most significant bit of x is " << (x >> (8*sizeof(x)-1)) << endl;
	cout << "The most significant bit of y is " << (y >> (8*sizeof(x)-1)) << endl;
	
	cout << "Type: \"int\"; Size: " << sizeof(x) << " bytes; Minimum value: "<< INT_MIN << "; Maximum value: "<< INT_MAX << ";" << endl;
	cout << "Type: \"unsigned int\"; Size: " << sizeof(y) << " bytes; Minimum value: "<< 0 << "; Maximum value: "<< UINT_MAX << ";" << endl;
	cout << "Type: \"signed char\"; Size: " << sizeof(a) << " bytes; Minimum value: "<< CHAR_MIN << "; Maximum value: "<< CHAR_MAX << ";" << endl;
	cout << "Type: \"short int\"; Size: " << sizeof(b) << " bytes; Minimum value: "<< SHRT_MIN << "; Maximum value: "<< SHRT_MAX << ";" << endl;
	cout << "Type: \"long int\"; Size: " << sizeof(c) << " bytes; Minimum value: "<< LONG_MIN << "; Maximum value: "<< LONG_MAX << ";" << endl;
	cout << "Type: \"long long int\"; Size: " << sizeof(d) << " bytes; Minimum value: "<< LLONG_MIN << "; Maximum value: "<< LLONG_MAX << ";" << endl;
	cout << "Type: \"unsigned char\"; Size: " << sizeof(e) << " bytes; Minimum value: "<< 0 << "; Maximum value: "<< UCHAR_MAX << ";" << endl;
	cout << "Type: \"unsigned short int\"; Size: " << sizeof(f) << " bytes; Minimum value: "<< 0 << "; Maximum value: "<< USHRT_MAX << ";" << endl;
	cout << "Type: \"unsigned long int\"; Size: " << sizeof(g) << " bytes; Minimum value: "<< 0 << "; Maximum value: "<< ULONG_MAX << ";" << endl;
	cout << "Type: \"unsigned long long int\"; Size: " << sizeof(h) << " bytes; Minimum value: "<< 0 << "; Maximum value: "<< ULLONG_MAX << ";" << endl;
	cout << "Type: \"float\"; Size: " << sizeof(i) << " bytes; Minimum value: "<< FLT_MIN << "; Maximum value: "<< FLT_MAX << ";" << endl;
	cout << "Type: \"double\"; Size: " << sizeof(j) << " bytes; Minimum value: "<< DBL_MIN << "; Maximum value: "<< DBL_MAX << ";" << endl;
	cout << "Type: \"long double\"; Size: " << sizeof(k) << " bytes; Minimum value: "<< LDBL_MIN << "; Maximum value: "<< LDBL_MAX << ";" << endl;
	
	return 0;
}