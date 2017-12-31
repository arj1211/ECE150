//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>

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
// Class declaration; modify but do not remove
							 
class StudentGrades 
{
public:
    // Supported statistics
    int   minimum();
    float average();
    int   maximum();
    float popStdDev();
    float smplStdDev();
    int   numModes();
    int   mode(const int modeNumber);
    int   histogram(const int bucketNumber);

    // Populating the data and writing out results
    int  readCSV(const char filename[]);
    int  writeStats(const char filename[]);
    
    // Some supporting functions
    bool validStudentIDs(const int minAcceptableID, const int maxAcceptableID);
    int  numRejects();
    int  reject(const int rejectNumber);

    // Constructor and Destructor
    StudentGrades();
    ~StudentGrades();

private:
    // It is up to you what you store here
};


//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

int StudentGrades::minimum()
{
    return -1;
}

float StudentGrades::average()
{
    return -1;
}

int StudentGrades::maximum()
{
    return -1;
}

float StudentGrades::popStdDev()
{
    return -1;
}

float StudentGrades::smplStdDev()
{
    return -1;
}

int StudentGrades::numModes()
{
    return -1;
}

int StudentGrades::mode(const int modeNumber)
{
    return -1;
}

int StudentGrades::histogram(const int bucketNumber)
{
    return -1;
}

int StudentGrades::readCSV(const char filename[])
{
    return -1;
}

int StudentGrades::writeStats(const char filename[])
{
    return -1;
}

bool StudentGrades::validStudentIDs(const int minAcceptableID, const int maxAcceptableID)
{
    return false;
}

int StudentGrades::numRejects()
{
    return -1;
}

int StudentGrades::reject(const int rejectNumber)
{
    return -1;
}

StudentGrades::StudentGrades()
{

}

StudentGrades::~StudentGrades()
{
    //Please clean up
}
		

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[]) 
{

    StudentGrades grades;
    //formatting
    cout << endl;

    if (!grades.readCSV(args[1]))
    {
        cout << "CSV read success" << endl;

    } 
    else
    {
        cout << "CSV read fail" << endl;
    }

    cout << "Min: " << grades.minimum() << endl;
    cout << "Max: " << grades.maximum() << endl;

    if (!grades.writeStats(args[1]))
    {
        cout << "Stats write success" << endl;

    } 
    else
    {
        cout << "Stats write fail" << endl;
    }
    //formatting
    cout << endl;

    return 0;

  
}
#endif
