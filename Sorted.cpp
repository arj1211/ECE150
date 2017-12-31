// I GOT PERF ON PUBLIC AND RELEASE TESTS ON FIRST RUN OF CODE AND FIRST SUBMISSION, I AM CODE GOD
//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// #defines, enum, and function declarations; do not remove
//

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself
#define NaN std::numeric_limits<float>::quiet_NaN() // (comes from <limits>)

enum sortType { ASCENDING, DESCENDING, UNKNOWN, UNSORTED };

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort);
bool sorted(const float data[]);

//////////////////////////////////////////////////////////////
//
// Your code here ...
// 
//

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort) 
{
  // ...
	if (typeOfSort==UNSORTED) return false;

	if (isNaN(data[currentDataItem]))
	{
		return true; // got to the end of the sequence without returning false, so must be sorted
	}

	if (currentDataItem==0)
	{
		// the very first item in sequence is the currentDataItem...
		if (isNaN(data[currentDataItem+1]) || isNaN(data[currentDataItem+2]))
		{
			return true; 
			// if currentDataItem is the first item,
			// and either the next one or the one after that 
			// is NaN (meaning the sequence is either 1 or 
			// 2 iterms long), it is sorted
		}
		else
		{
			// at this point, the sequence's size>=4

			// 1. if the next element (second item) is 
			// greater than first item, mark it as ASCENDING
			// and call isSorted
			if (data[currentDataItem+1]>data[currentDataItem])
			{
				return isSorted(data, currentDataItem+1, ASCENDING);
			}

			// 2. if the next element (second item) is
			// lower than first item, mark it as DESCENDING
			// and call isSorted

			if (data[currentDataItem+1]<data[currentDataItem])
			{
				return isSorted(data, currentDataItem+1, DESCENDING);
			}

			// 3. if the next element (second item) is 
			// equal to the first item, mark it as UNKNOWN
			// and call isSorted

			if (data[currentDataItem+1]==data[currentDataItem])
			{
				return isSorted(data, currentDataItem+1, UNKNOWN);
			}

		}
	}

	switch (typeOfSort)
	{
		case ASCENDING:
			/*
			what are the different ways it can still be ASCENDING?
			- if previous item <= currentDataItem
			-> if this not the case, meaning the sequence WAS ASCENDING UPTIL
				the currentDataItem but the currentDataItem<previous item, 
				the sequence cannot be considered ASCENDING anymore, and is UNSORTED
			*/
		if (data[currentDataItem-1]<=data[currentDataItem])
			return isSorted(data, currentDataItem+1, ASCENDING);
		else
			return isSorted(data, currentDataItem+1, UNSORTED);


		case DESCENDING:
			/*
			what are the different ways it can be DESCENDING?
			- if the previous item >= currentDataItem
			-> if this is not the case, meanin the sequence WAS DESCENDING UPTIL
				the currentDataItem but the currentDataItem>previous item,
				the sequence cannot be considered DESCENDING anymore, and is UNSORTED
			*/
		if (data[currentDataItem-1]>= data[currentDataItem])
			return isSorted(data, currentDataItem+1, DESCENDING);
		else
			return isSorted(data, currentDataItem+1, UNSORTED);


		case UNKNOWN:
			/*
			when does this happen? what does it imply about whether the sequence 
			is sorted or not?
			- this happens when the previous item is equal to the current item
			is equal to the next item, given that the next item is not NaN
				-> this only ever happens before there is a change in the value 
				of the item as we go further into the sequence. 
				Ex. 0 0 0 0 0 0 0 1 , would be UNKNOWN until 
				data[currentDataItem] was 1
			
			*/
		if (data[currentDataItem]>data[currentDataItem-1])
		{
				// the sequence was UNKNOWN, but is now ASCENDING
			return isSorted(data, currentDataItem+1, ASCENDING);
		}
		else if (data[currentDataItem]<data[currentDataItem-1])
		{
				// the sequence was UNKNOWN, but is now DESCENDING
			return isSorted(data, currentDataItem+1, DESCENDING);
		}
		else
		{
				// still UNKNOWN... which is fine cuz its TECHNICALLY sorted up till this point
			return isSorted(data, currentDataItem+1, UNKNOWN);
		}
	}
}

bool sorted(const float data[]) {
  // ...
	return isSorted(data, 0, UNKNOWN);
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {

  // Some test driver code here ....
	float data[] = {1, 2, 4, 5, 9, NaN};
  //Sorted:
	float data1[] = {0,1,2,3,4,5,6,NaN};
	float data2[] = {1,-1,-3,-5,-9,NaN};
	float data3[] = {0,0,0,0,0,0,0,0,NaN};
	float data4[] = {1,0,0,0,0,0,0,NaN};
	float data5[] = {-1,0,0,0,0,0,NaN};
	float data6[] = {-10,-1,0,1,10,NaN};
	float data7[] = {1,2,3,3,3,4,5,5,6,NaN};
	float data8[] = {1,NaN};
	float data9[] = {-9,NaN};
	float data10[] = {1,0,NaN};
	float data11[] = {7,0,NaN};
	float data12[] = {6,66,NaN};
	float data13[] = {0,0,NaN};

//Unsorted: 
	float data14[] = {-1,-1,-1,-1,-1,-1,0,-1,NaN};
	float data15[] = {0,1,2,3,4,5,6,7,8,9,1,NaN};
	float data16[] = {-1,0,1,0,-1,0,1,0,NaN};



	cout << "data1 = {";
	for (int i = 0; !isNaN(data1[i]); i++)
	{
		if (isNaN(data1[i+1]))
			cout << data1[i] << "}";
		else
			cout << data1[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data1))
		cout << "data1 is sorted" << "\n~~~\n";
	else
		cout << "data1 is not sorted" << "\n~~~\n";

	cout << "data2 = {";
	for (int i = 0; !isNaN(data2[i]); i++)
	{
		if (isNaN(data2[i+1]))
			cout << data2[i] << "}";
		else
			cout << data2[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data2))
		cout << "data2 is sorted" << "\n~~~\n";
	else
		cout << "data2 is not sorted" << "\n~~~\n";

	cout << "data3 = {";
	for (int i = 0; !isNaN(data3[i]); i++)
	{
		if (isNaN(data3[i+1]))
			cout << data3[i] << "}";
		else
			cout << data3[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data3))
		cout << "data3 is sorted" << "\n~~~\n";
	else
		cout << "data3 is not sorted" << "\n~~~\n";

	cout << "data4 = {";
	for (int i = 0; !isNaN(data4[i]); i++)
	{
		if (isNaN(data4[i+1]))
			cout << data4[i] << "}";
		else
			cout << data4[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data4))
		cout << "data4 is sorted" << "\n~~~\n";
	else
		cout << "data4 is not sorted" << "\n~~~\n";

	cout << "data5 = {";
	for (int i = 0; !isNaN(data5[i]); i++)
	{
		if (isNaN(data5[i+1]))
			cout << data5[i] << "}";
		else
			cout << data5[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data5))
		cout << "data5 is sorted" << "\n~~~\n";
	else
		cout << "data5 is not sorted" << "\n~~~\n";

	cout << "data6 = {";
	for (int i = 0; !isNaN(data6[i]); i++)
	{
		if (isNaN(data6[i+1]))
			cout << data6[i] << "}";
		else
			cout << data6[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data6))
		cout << "data6 is sorted" << "\n~~~\n";
	else
		cout << "data6 is not sorted" << "\n~~~\n";

	cout << "data7 = {";
	for (int i = 0; !isNaN(data7[i]); i++)
	{
		if (isNaN(data7[i+1]))
			cout << data7[i] << "}";
		else
			cout << data7[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data7))
		cout << "data7 is sorted" << "\n~~~\n";
	else
		cout << "data7 is not sorted" << "\n~~~\n";

	cout << "data8 = {";
	for (int i = 0; !isNaN(data8[i]); i++)
	{
		if (isNaN(data8[i+1]))
			cout << data8[i] << "}";
		else
			cout << data8[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data8))
		cout << "data8 is sorted" << "\n~~~\n";
	else
		cout << "data8 is not sorted" << "\n~~~\n";

	cout << "data9 = {";
	for (int i = 0; !isNaN(data9[i]); i++)
	{
		if (isNaN(data9[i+1]))
			cout << data9[i] << "}";
		else
			cout << data9[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data9))
		cout << "data9 is sorted" << "\n~~~\n";
	else
		cout << "data9 is not sorted" << "\n~~~\n";

	cout << "data10 = {";
	for (int i = 0; !isNaN(data10[i]); i++)
	{
		if (isNaN(data10[i+1]))
			cout << data10[i] << "}";
		else
			cout << data10[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data10))
		cout << "data10 is sorted" << "\n~~~\n";
	else
		cout << "data10 is not sorted" << "\n~~~\n";

	cout << "data11 = {";
	for (int i = 0; !isNaN(data11[i]); i++)
	{
		if (isNaN(data11[i+1]))
			cout << data11[i] << "}";
		else
			cout << data11[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data11))
		cout << "data11 is sorted" << "\n~~~\n";
	else
		cout << "data11 is not sorted" << "\n~~~\n";

	cout << "data12 = {";
	for (int i = 0; !isNaN(data12[i]); i++)
	{
		if (isNaN(data12[i+1]))
			cout << data12[i] << "}";
		else
			cout << data12[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data12))
		cout << "data12 is sorted" << "\n~~~\n";
	else
		cout << "data12 is not sorted" << "\n~~~\n";

	cout << "data13 = {";
	for (int i = 0; !isNaN(data13[i]); i++)
	{
		if (isNaN(data13[i+1]))
			cout << data13[i] << "}";
		else
			cout << data13[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data13))
		cout << "data13 is sorted" << "\n~~~\n";
	else
		cout << "data13 is not sorted" << "\n~~~\n";

	cout << "data14 = {";
	for (int i = 0; !isNaN(data14[i]); i++)
	{
		if (isNaN(data14[i+1]))
			cout << data14[i] << "}";
		else
			cout << data14[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data14))
		cout << "data14 is sorted" << "\n~~~\n";
	else
		cout << "data14 is not sorted" << "\n~~~\n";

	cout << "data15 = {";
	for (int i = 0; !isNaN(data15[i]); i++)
	{
		if (isNaN(data15[i+1]))
			cout << data15[i] << "}";
		else
			cout << data15[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data15))
		cout << "data15 is sorted" << "\n~~~\n";
	else
		cout << "data15 is not sorted" << "\n~~~\n";

	cout << "data16 = {";
	for (int i = 0; !isNaN(data16[i]); i++)
	{
		if (isNaN(data16[i+1]))
			cout << data16[i] << "}";
		else
			cout << data16[i] << ", ";
	}
	cout << "\n~~~\n" << "\n~~~\n";
	if (sorted(data16))
		cout << "data16 is sorted" << "\n~~~\n";
	else
		cout << "data16 is not sorted" << "\n~~~\n";

	return 0;
}

#endif