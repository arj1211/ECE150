//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//#include <cstdlib>
#include <fstream>
//#include <cmath>
#include <iostream>

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

int maxNumErrors = 10;

/*
  
  int* means the parameter is a pointer; you will need to allocate space for it using new[];
  int*& means the parameter is a pointer that is passed by reference, not value, so when you allocate 
  space and assign it to rejects, that pointer address will be "returned" to the calling 
  function (more precisely, the change to the parameter in the histogram function is seen 
  in the calling function).
  Access to an int pointer is as you wish: you can use pointer or array notation.  Thus:
  int* x = new int[23];
  allows array elements in x to be accessed as either:
  x[13] = 234;
  or
  *(x+13) = 234;
  


  Just a quick warning about parsing files (like in the 3rd assignment). 
  Windows adds a carriage return ('\r') as well as a newline at the end 
  of each line. The file reader will read until the newline, but still 
  include the carriage return in the string. Easiest thing to do is to 
  just treat '\r' as another whitespace character.


  The main test function declares  
 
 
       int* rejectedRecords
 
  and tries to delete it after all my code is run with
 
     delete [] rejectedRecords;
 
  My issue is that the delete is not happening so it 
  stalls my program until I get a core dumped. It's passed 
  to my function as the parameter int*& rejects and I have 
  just been adding rejected line numbers to the array with 

     rejects [countInvalids++] = fileLineNumber; 

  which is probably not right. How should I be appending things to the rejects array?
   
  Note that if I remove the delete [] rejectedRecords in the main, 
  then it works (which makes sense because the array is not 
  being NEW'd in the main function, so does that mean I should new it in my histogram function?)
  
  That's correct, you will need to create a new array (using new) somewhere in the histogram function.
 
  The main function creates a pointer rejectedRecords, but that pointer doesn't point to 
  any data yet. Just like how any int that is declared will have a value even if you do 
  not initialize it, the pointer will have whatever garbage was in the memory before it, 
  and that garbage will be interpreted as an address when you do something like 
  rejects [countInvalids++] = fileLineNumber; You are not actually writing to an array 
  because no one created one yet. This is bad.
 
  The intended procedure is that your function allocates the array with new, and points 
  rejects to it. Because the pointer is passed by reference you will directly change the 
  pointer passed by the calling function so it now has a pointer to the array you created. 
  That way you can control what size the array is, so whoever is calling the function does 
  not have to figure out before hand what size array to give you. This is noted in the lab document:
   
  "Note that the rejects array must be dynamically allocated in your function"
  
  The only comment I will add to the student's answer is that the template should 
  probably have set the rejectedRecords pointer to 0 when it was declared so as to 
  ensure that if the function made no change to it that the delete[] would not fail for that reason.


  Does anybody know what Error03NullArray.py checks for? I can't seem to 
  figure out what it means based on its name.
  So there are two arrays in the parameter list that are not 
  const -- histogram and rejects. Think which one can cause you trouble.

  Does anyone know what Error04 - invalid characters is testing for. 
  It says its expected result is -1 so it must be error checking of some sort.
  I remember reading on the outline that there will be nothing other 
  than whitespace, tabs, commas, and numbers in the grades file. So what 
  checking should be done for the file name. Isn't checking to see if it 
  can open the file sufficient error checking to see if the name is correct.

  I've included invalid character checking in mine and am able to pass 
  that test. It seems to me that the lab document is incorrect and you 
  should catch invalid characters, and return -1 if you encounter any.

  I seem to be failing release test case Func05GradeLow for FileReading.cpp
  From its name it appears to be testing something to do with a 
  low grade except I make sure only valid grades [0,100] are added 
  to my histogram function.
  What exactly is this test case looking for? My histogram is able to 
  handle grades at 0 so I am unsure what a low grade would be.
  *EDIT* Apparently negative grades can be a thing
  In my parsing should I reject it as soon as I see a negative sign? or 
  should I compute the entire number just in case there is a double negative 
  making the number positive? 

  I think it checks to see that you reject negative grades. The dash 
  before the negative numbers might be breaking your code.
  Response to edit: I don't think that they're going to give you double negatives
  Does your histogram function return -1 if there is a negative sign, or 
  does it ignore the negative and count it as an error?
  If there is a negative sign in the mark, then it is a valid number, but 
  outside the valid range of marks (0 to 100) so you reject the line and 
  add it to the rejects array.

  However, you do not know how many rejects you will have. Either you 
  need some way to store data that you can expand when needed, or the 
  lab document specfies you can declare a global variable (ie. outside 
  your function) int maxNumErrors and set it to the maximum number of 
  rejects you will handle. Then you can just return -1 if you ever 
  have more rejects than that. You should make it past all test cases 
  if you do this, but there could be some bonus points in the secret 
  tests for handling unlimited number of rejects.

  if (histogram == NULL){
    return -1;
  }

*/

using namespace std;


int histogram(const char filename[], int histogram[10], 
  const int minAcceptableID, const int maxAcceptableID,
  int*& rejects) {
  // Your code here ...

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
  
  int numOfRejects = 0;
  rejects = new int[10];

  //cout << "rejects: " << rejects << endl;


  while (!done) 
  { // Read from file
    ++fileLineNumber;
    if (!infile.getline(line, maxLineLength)) 
    { // Get next line
      if (infile.eof()) 
      { // End of file
        done = true;
      }
      else 
      { // Some error reading file
        //cout << "Reaching eof at " << fileLineNumber << endl;
        return -1;
      }
    }
    
    // parseLine(line); // Parse the line (can use state machine)
    //cout << "line " << fileLineNumber << ": " << line << endl;
    
    //cout << "current num of rejects: " << numOfRejects << endl;

    int i = 0;
    int studentID = 0;
    bool comma = false;
    int negative = 1;
    int grade = 0;
    
    while (line[i]!=0)
    {
      if (line[i]==' ' || line[i]=='\t' || line[i]=='\r')
      {
        
        continue;
      }
      else if (line[i]=='-')
      {
       // rejects[numOfRejects++]=fileLineNumber;
        negative=-1;
      }
      else if (line[i]>='0' && line[i]<='9')
      {
        if (!comma)
        {
          // still reading in studentID
          studentID = 10*studentID+(line[i]-'0');
        }
        else
        {
          // reading in grade
          if (grade<0) grade=-grade;
          grade = (10*grade + (line[i]-'0'))*negative;
        }
      }
      else if (line[i]==',')
        comma=true;
      else 
      {
        //cout << "invalid char: " << line[i] << endl;
        //rejects[numOfRejects++]=fileLineNumber;
        return -1;
      }
      //cout << line[i];
      i++;
    }


    if (line[0]!='\r')
    {
      if (grade<0 || grade>100 || studentID<minAcceptableID || studentID>maxAcceptableID)
      {
        rejects[numOfRejects] = fileLineNumber;
        numOfRejects++;
      }
      else
      {
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
    }

  }

  //numOfRejects--;
  //histogram[0]--;
  return (numOfRejects>10)?-1:numOfRejects;

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
//int maxNumErrors = 10;
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
  int retCode = histogram(argv[1], buckets, 0, 10, rejectedRecords);
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
