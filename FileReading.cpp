//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//#include <stdlib.h>
#include <fstream>

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
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

using namespace std;

int histogram(const char filename[], int histogram[10], 
  const int minAcceptableID, const int maxAcceptableID,
  int*& rejects);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//

int histogram(const char filename[], int histogram[10], 
  const int minAcceptableID, const int maxAcceptableID,
  int*& rejects) 
{


  if (minAcceptableID>maxAcceptableID) return -1;

  if (histogram==NULL)
    return -1;



  const int maxLineLength = 100;
  char line[maxLineLength];
  ifstream infile; // declare the file object
  infile.open(filename); // open the file
  
  if (!infile.is_open())
    return -1; // Unable to open file
  
  bool done = false;
  int fileLineNumber = 0;
  
  for (int i = 0; i<10; i++)
    histogram[i]=0;

  int numberOfRejects = 0;

  int rejectSize = 100;
  rejects = new int[rejectSize];

  while (!done) 
  { 
    // Read from file
    ++fileLineNumber;
    if (!infile.getline(line, maxLineLength)) 
    { // Get next line
      if (infile.eof()) 
      { // End of file
        done = true;
      }
      else 
      { // Some error reading file
        return -1;
      }
    }


  // parseLine(line); // Parse the line
  // (can use state machine)
  // doHistogramStuff();


    int i = 0;
    int studentID = 0;
    int grade = 0;
    
    bool comma = false;
    bool rejekt = false;


    while (line[i]!=0 && line[i]!='\r')
    {
      if (rejekt) break;
      // if its whitespace or tabs, not reject just continue
      if (line[i]==' ' || line[i]=='\t' && !rejekt);
      // if its a number
      else if (line[i]<='9' && line[i]>='0' && !rejekt)
      {  
        // if comma didn't occur yet, we're reading in student ID
        if (!comma && !rejekt)
        {
          while (line[i]<='9' && line[i]>='0' && !rejekt)
          {
            studentID = 10*studentID+(line[i]-'0');
            // locally increment character, keep reading in numbers
            i++;
          }
          i--;
          // as soon as a non-number character appears, check if minAcceptableID<studentID<maxAcceptableID
          if (studentID<minAcceptableID || studentID>maxAcceptableID)
          {
            // if studentID invalid, reject and break
            rejects[numberOfRejects++] = fileLineNumber;
            if (numberOfRejects>=rejectSize)
              return -1;
            rejekt=true;
          }
        }
        else if (!rejekt)
        {
        // if comma did occur, we're reading in grade
          while (line[i]<='9' && line[i]>='0' && !rejekt)
          {
            grade = (10*grade + (line[i]-'0'));
            // locally increment character, keep reading in
            i++;
          }
          i--;
          // as soon as non-number character appears, check if 0<=grade<=100
          if (grade>=0 && grade <= 100 && !rejekt)
          {
            // if grade valid, put into right bucket
            if (grade>=0 && grade <=9)
              histogram[0]++;
            else if (grade>=10 && grade<=19)
              histogram[1]++;
            else if (grade>=20 && grade<=29)
              histogram[2]++;
            else if (grade>=30 && grade<=39)
              histogram[3]++;
            else if (grade>=40 && grade<=49)
              histogram[4]++;
            else if (grade>=50 && grade<=59)
              histogram[5]++;
            else if (grade>=60 && grade<=69)
              histogram[6]++;
            else if (grade>=70 && grade<=79)
              histogram[7]++;
            else if (grade>=80 && grade<=89)
              histogram[8]++;
            else if (grade>=90 && grade<=100)
              histogram[9]++;
          }
          else
          {
            // if grade invalid, reject and break
            rejects[numberOfRejects++] = fileLineNumber;
            if (numberOfRejects>=rejectSize)
              return -1;
            rejekt=true;
          }
        }
      }
      else if (line[i]==',' && !rejekt) comma=true;
      else if (line[i]=='-')
      {
        rejects[numberOfRejects++] = fileLineNumber;
        if (numberOfRejects>=rejectSize)
          return -1;
        rejekt=true;
      }
      //~~~~~~~~~
      else
      {
        // if its not any of the above characters, its invalid input so terminate function
        return -1;
      }
      i++;
    }
  }

  return numberOfRejects;
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

  // Some test driver code here ....
  if (argc < 2) {

  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int buckets[numBuckets];

  for (int i = 0; i<numBuckets; i++)
    buckets[i]=0;

  int* rejectedRecords;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
    cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
       cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
     else
       cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
     if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i)
       cout << " " << rejectedRecords[i];
     cout << endl;
     delete[] rejectedRecords;
   }
 }

 return 0;
}

#endif
