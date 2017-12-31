#include <fstream>
#include <climits>
#include <cmath>
#include <limits>
#ifndef MARMOSET_TESTING
#include <iostream>
#endif
#ifndef MARMOSET_TESTING
struct Student{
	int studentID;
	int grade;
};
struct Dataset{
	int numStudents;
	Student* students;
};
struct Rejects{
	int numRejects;
	int* rejects;
};
struct Mode{
	int numModes;
	int* modes;
};
struct Statistics{
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	Mode  mode;
	int   histogram[10];
};
#endif
int readCSV(const char filename[],const int minAcceptableID, 
	const int maxAcceptableID,Dataset& data, 
	Rejects& rejects);
int computeStatistics(Dataset& data, Statistics& stats);
int writeCSV(const char filename[], const Statistics& stats);
bool statistics(const float dataset[], const int size,
	float& min, float& avg, float& max,
	float& popSD, float& smplSD, float& mdn);
float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);
bool selection(int dataset[], const int size);

using namespace std;

char* statName(const char filename[])
{	
	int lenFileName = 0;
	for (int i = 0; filename[i] != 0; i ++)
	{
		if (filename[i] == '.' && filename[i+1] != 'c')
			return NULL;
		else if (filename[i] == '.')
		{
			lenFileName = i ;
			break;
		}
		else if (filename[i+1] == 0)
		{
			lenFileName = i + 1;
			break;
		}
	}
	char *correctFileName = new char[lenFileName + 5];
	for (int i = 0; filename[i] != 0; i++)
		correctFileName[i] = filename[i];
	correctFileName[lenFileName] = '.';
	correctFileName[lenFileName + 1] = 's';
	correctFileName[lenFileName + 2] = 't';
	correctFileName[lenFileName + 3] = 'a';
	correctFileName[lenFileName + 4] = 't';
	correctFileName[lenFileName + 5] = '\0';

	return correctFileName;	
}
int mode(Dataset& data, const int size, Statistics& stats) // in here somewhere, 
// error is for 100000+ numbers
{
	if (size<=0) return -1;
	int d[size];
	for (int i = 0; i < size; i++)
		d[i]=data.students[i].grade;
	sort(d,size);

	stats.mode.modes = new int[size];
	for (int i = 0; i < size; ++i)
	{
		stats.mode.modes[i]=0;
	}

	if (size==1)
	{
		return 1;
	}

	stats.mode.modes[0]=d[0];

  	int largestFreq = 1; // counts the number of occurences a number in data must have to be considered a mode
  	int numberOfTimesTheCurrentNumberAppears = 1;
  	int modeIndex = 0; // index into mode[] . modeIndex+1 is the number of modes thus far
  	//mode[modeIndex];
  	int currNum = d[0];
  	for ( int i=1; i<size;i++)
  	{
  		if ( currNum == d[i] ) 
  		{
  			numberOfTimesTheCurrentNumberAppears++;
  		}
  		else
  		{
  			numberOfTimesTheCurrentNumberAppears=1;
  			currNum=d[i];
  		}

  	  	if ( numberOfTimesTheCurrentNumberAppears > largestFreq )
  	  	{
  	  		modeIndex=0;
  	  		largestFreq = numberOfTimesTheCurrentNumberAppears;
  	  		stats.mode.modes[modeIndex] = currNum;
  	  	}

  	  	else if ( numberOfTimesTheCurrentNumberAppears == largestFreq ) 
  	  	{
  	  		modeIndex++;
  	  		stats.mode.modes[modeIndex]=d[i];
  	  	}
	}	
	
	stats.mode.numModes = modeIndex+1;

	return stats.mode.numModes;
}

// void expand(Dataset& data, int id, int grd)
// {

// 	int numStudents = data.numStudents;

// 	Student* newkids = new Student[numStudents+1];

//     for(int i = 0; i < numStudents; i++) 
//     {
// 		newkids[i].grade = data.students[i].grade;
// 		newkids[i].studentID = data.students[i].studentID;
//     }

//     newkids[numStudents].grade = grd;
//     newkids[numStudents].studentID = id;

//     numStudents++;

//     delete[] data.students; // Deallocate a. Accesses are no longer legal

//     data.students = new Student[numStudents];
//     data.numStudents = numStudents;
//     data.students = newkids;

//     delete[] newkids;
// }
void expand(Rejects& reject, int fileLineNumber)
{
	int numRejects = reject.numRejects;

	int* r = new int[numRejects+1];

	for (int i = 0; i < numRejects; ++i)
	{
		r[i]=reject.rejects[i];
	}
	r[numRejects]=fileLineNumber;
	numRejects++;
	delete[] reject.rejects;
	reject.rejects = new int[numRejects];
	reject.rejects = r;
	reject.numRejects = numRejects;
	delete[] r;
}

bool sort(int dataset[], const int size)
{
	bool tmp = selection(dataset, size);
	return true;
}
bool selection(int dataset[], const int size)
{
	int max = INT_MIN;
	int maxIndex = 0;
	if(size == 1)
		return true;
	for(int i = 0; i < size; i++)
		if(dataset[i] > max)
		{
			max = dataset[i];
			maxIndex = i; 
		}
	int temp = dataset[size-1];
	dataset[size-1] = max;
	dataset[maxIndex] = temp;
	return selection(dataset, size-1); 
}
float minimum(const float dataset[], const int size) 
{

	float n = dataset[0];
	int argind = 1;
	while(argind < size)
	{
		float val = dataset[argind];

		if(val < n)
			n = val;

		argind++;
	}
	return n;
}
float average(const float dataset[], const int size) 
{
	float tot = 0;
	int argind2 = 0;

	while(argind2 < size)
	{
		float val2 = dataset[argind2];
		tot += val2;
		argind2++;
	}
	float avg = tot/(float)size;
	return avg;   
}
float maximum(const float dataset[], const int size) 
{
	float mmax = dataset[0];
	int argind3 = 1;

	while(argind3 < size)
	{
		float value3 = dataset[argind3];
		if(value3 > mmax)
			mmax = value3;
		argind3++;
	}
	return mmax;
}
float popStdDev(const float dataset[], const int size) 
{

	if(size == 0){
		return std::numeric_limits<float>::quiet_NaN();
	}

	float sum = 0;
	float tmp = 0;
	int k = 0;

	while(k < size){
		float value4 = dataset[k];
		tmp = value4 - average(dataset, size);
		sum += pow(tmp,2);
		k++;
	}

	float poptemp = sum*(1/(float)size);
	float popStdDev = sqrt(poptemp);
	return popStdDev;
}
float smplStdDev(const float dataset[], const int size) 
{

	if(size == 1){
		return std::numeric_limits<float>::quiet_NaN();
	}
	
	float add = 0;
	float tmpry = 0;
	float t = 0;
	int j = 0;

	while(j < size){
		float value5 = dataset[j];
		tmpry = value5 - average(dataset, size);
		add += pow(tmpry,2);
		j++;
	}

	float sampletemp = add*((float)1/(float)(size-1));
	float sampleStdDev = sqrt(sampletemp);
	return sampleStdDev;
}
using namespace std;
/*
A loaded line may be one with just numbers no commas, but still less than the 
length of line (source: fixed that and passed the test)
*/
/*
Func01Average.py
I'd check that you're allocating space properly for the data.students[] array and the reject.rejects[] array. 
You have to resize and reallocate memory to them as your program runs, so as to ensure no undefined behavior 
happens. Marmo's really picky about that. 
*/


/*
Func12LoadedLine.py
is loaded line just bunch of numbers such as 12423536367457547 ready to crash my machine?
From what I'm hearing from other people, it is pretty much that. Your parsing code should reject
that because of lack of comma, and your integer conversion code should return an error because 
of overflow, so there are two ways to catch it.
*/

/*
Reject a line if:
ID is outside range of [minAcceptableID, maxAcceptableID]
Grade is outside range of [0, 100]
It will not parse correctly (missing comma for example)
There are invalid characters
 
Never ignore a line (maybe if it's all whitespace, but I have not seen any 
tests for this because people still succeed regardless of whether they ignore or reject it)
*/

/*
make sure to initialize every variable (even those passed to you through structure)
also make sure you reject the right input (see the other post on rejection) if 
you can't pass the release cases on average min....
*/

/*
FileWriting: Func09ChangeExtension and Func10NoExtension
I can't get these two release cases to pass and I was wondering if anyone who has gotten these two could clarify.
We are only expected to deal with 2 cases with the file names correct? Either 
the filename[] contains a .csv or has no extension at all.
For readCSV: 
if it contains .csv -> read original filename
else tack on .csv -> read updated filename
For writeCSV
if it contains a .csv -> remove extension and add .stat -> write with update filename
else tack on a .stat -> write with updated filename
Both of these are done before the file is read/written and it works as it should on my 
computer, but I still can't get them on marmoset. Anyone see what I might be doing wrong?

Your doing right. Make sure that you error check the arrays in the stats struct. If an array is 
null when you are expecting it to be not null then you should return error.
*/

/*
the release cases are not about how good your min/max calculation is....
it is about how good you are at rejecting invalid lines
 
22212345,34 is a valid input
 
however 222 12345,34 is not
22212345,34, is also an invalid input because of the extra commas
                   22212345                          ,34                        is a good input
*/

// Spaces between numbers is an error, ensure that you are rejecting such lines

/*
Array Zeroing
Can someone help explain what this means? Which arrays do I need to fill with zeros?

This means that one of the arrays in the function has not had its elements all set to zero, 
and so if they do not get modified, they will be at some undefined value. Of course, this 
doesn't matter for most arrays. The only arrays in the program are the students array, the 
rejects array, the mode array, and the histogram array. Of those, there's only one where all 
elements will all be accessed under normal conditions and that you should therefore zero. If 
you need a hint, think back to the histogram question on the midterm.
*/


//Make sure you're allocating space properly to the arrays data.students[] and reject.rejects[]
//And also make sure your reject array actually has the proper rejects!! Thats how I fixed mine
/*
^^ in case you're still going by my old piazza posts, note that they changed test cases so you
need to add lines with invalid characters to the rejects array instead of just skipping over them
*/

/*
what I personally did was that everytime I'd need to add something to the 
array (i.e. make it larger), I'd copy it into another array first, reinitialize the original 
array with the larger size, then copy it back and add in the last element
If you're doing it very often, it's useful to write a method that just does this
As far as test cases go, I just kinda dicked around with the file, I didn't do any really 
conclusive testing, I pretty much just used marmoset to brute force test
*/

int readCSV(const char filename[],const int minAcceptableID, 
	const int maxAcceptableID,Dataset& data, 
	Rejects& rejects)
{
	if (minAcceptableID>maxAcceptableID) return -1;
	bool seenDot = false;
	int i = 0;
	for (; filename[i]!=0; i++)
	{
		if (filename[i]=='.' && seenDot) return -1;
		else if (filename[i]=='.') 
		{
			seenDot = true;
			break;
		}	
	}
	char* newfilename = new char[i+4];
	if (!seenDot)
	{
		int i = 0;
		for (; filename[i]!=0; i++)
			newfilename[i]=filename[i];
		newfilename[++i]='.';
		newfilename[++i]='c';
		newfilename[++i]='s';
		newfilename[++i]='v';
	}
	else
	{
		// check if it actually is csv extension
		if (!(filename[i+1]=='c' && filename[i+2]=='s' && filename[i+3]=='v'))
			return -1;
	}
	const int maxLineLength = 100;
	char line[maxLineLength];
  	ifstream infile; // declare the file object
  	(seenDot)? infile.open(filename) : infile.open(newfilename); // open the file
  	if (!infile.is_open())
  	  return -1; // Unable to open file
  	bool done = false;
  	int fileLineNumber = 0;
  	int rejectSize = 10; // THIS LINE IS CRUCIAL, DONT CHANGE FROM 10
  	rejects.rejects = new int[1];
  	rejects.rejects[0]=0;
  	rejects.numRejects = 0;
  	data.students = new Student[100];
  	for (int i = 0; i < 100; ++i)
  	{
  		/* code */
	data.students[i].grade=0;
	data.students[i].studentID=0;
  	}
  	data.numStudents=0;

  	int data_index=0;

  	while (!done) 
  	{
  		++fileLineNumber;
  		if (!infile.getline(line, maxLineLength)) 
    	{
    		if (infile.eof()) 
    			done = true;
			else return -1;
    	}
    	int i = 0;
    	int studentID = 0;
    	int grade = 0;
    	bool comma = false;
    	bool rejekt = false;
    	bool studentIDseen = false;
    	bool gradeSeen = false;
    	bool invalidCharSeen = false;
    	
    	while (line[i]!=0 && line[i]!='\r') // goes till no more chars, SKIPS \r lines
    	{
    		if (rejekt) 
    		{
    			break;
    		}
    		else if (line[i]==',' && comma) // if multiple commas, its a reject
	    	{
	    		rejekt=true;
	    	}
	    	else if (line[i]==',')
    			comma=true;
	    	 // if its whitespace or tabs, not reject just continue
    		else if (line[i]==' ' || line[i]=='\t');// continue;
	    	  // if its a number
    		else if (line[i]<='9' && line[i]>='0')
    		{  
	    	    // if comma didn't occur yet, we're reading in student ID
    			if (!comma)
    			{
    				if (studentID) // in the case where theres [valid student id]    [valid student id]
    				{
    					rejekt=true;
    				} 
    				else // first time seeing studentID
    				{
    					studentIDseen=true;
    					while (line[i]<='9' && line[i]>='0')
    					{
    						studentID = 10*studentID+(line[i]-'0');
	    	        		// locally increment character, keep reading in numbers
    						i++;
    					}
    					i--;
    				}
    			}
    			else // must be reading grade, cuz hasnt been rejected, and a comma already occurred
    			{
    				if (grade) // in the case where theres [valid grade]    [valid grade]
    				{
    					rejekt=true;
    				} 
    				else
    				{
    					gradeSeen=true;
    					while (line[i]<='9' && line[i]>='0')
    					{
    						grade = (10*grade + (line[i]-'0'));
	    	        		// locally increment character, keep reading in
    						i++;
    					}
    					i--;

	    	  		}
	    	  	}
	    	}
	    	else // if its any other character, reject the line not the file necessarily
	    	{
	    		invalidCharSeen=true;
	    		rejekt=true;
	    	}
	    	i++;
	    }
	    //~~~~~~~~~~~~~~~~~~~~~~~~~~CURRENT LINE END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	    // at this point, there could be errors
	    // if saw the studentID but not grade
	    // if saw grade but not studentID
	    // if didnt see grade or studentID, but did see invalid char or comma

	    if (!rejekt && ( (studentIDseen && !gradeSeen) ||
	    		(gradeSeen && !studentIDseen) ||
	    		(!gradeSeen && !studentIDseen && (invalidCharSeen || comma) ) ) )
	    {
	  		rejekt=true;
	    }
	    

	    if (rejekt || grade<0 || grade>100 || studentID<minAcceptableID || studentID>maxAcceptableID)
	    {
	    	// rejection routine
	    	// rejects.rejects[reject_index++]=fileLineNumber;
	    	// cout << "rejected line " << fileLineNumber << endl;
	    	// if (rejects.numRejects==0)
	    	// {
	    	// 	rejects.rejects[0]=fileLineNumber;
	    	// 	rejects.numRejects++;
	    	// }
	    	// else
	    		expand(rejects, fileLineNumber);
	    	//rejects.numRejects++;
	    	if (rejects.numRejects>rejectSize)
				return -1;
	    }
	    else if (!rejekt && studentIDseen && gradeSeen)
	    {
	    	data.students[data_index].grade = grade;
	    	data.students[data_index++].studentID = studentID;
	    	// cout << "valid line " << fileLineNumber << endl;
    		// expand(data, studentID, grade);
    		data.numStudents++;
	    }
	}
	// cout << "rejected: " << rejects.numRejects << endl;
	// // cout << "s: " << data.numStudents << endl;

	// for (int i = 0; i < rejects.numRejects; ++i)
	// {
	// 	cout << rejects.rejects[i] << ", ";
	// }
	// cout << ";"<<endl;
	// for (int i = 0; i < data.numStudents; ++i)
	// {
	// 	cout << data.students[i].grade << "-";
	// 	cout<< data.students[i].studentID << ", ";
	// }
	// cout << ";studentsDone	" << endl<<endl;

	if (rejects.numRejects>=rejectSize)
				return -1;

	// cout << rejects.numRejects << endl;

	return (--rejects.numRejects<0)?0:rejects.numRejects;
}


int computeStatistics(Dataset& data, Statistics& stats)
{
	float s1 = 0;
	float s2 = 0;
	int* srtd = new int[data.numStudents];
	for (int i = 0; i < data.numStudents; i++)
		srtd[i] = data.students[i].grade;
	sort(srtd, data.numStudents);
	stats.minimum = srtd[0];
	stats.maximum = srtd[data.numStudents-1];
	for (int r = 0; r < data.numStudents; r++)
		s1 += srtd[r];
	stats.average = s1/data.numStudents;
	for (int j = 0; j < data.numStudents; j++)
		s2 += (srtd[j]-stats.average)*(srtd[j]-stats.average);
	stats.popStdDev = sqrt(s2/data.numStudents);
	stats.smplStdDev = sqrt(s2/(data.numStudents-1));
	mode(data, data.numStudents, stats);
  	if (stats.histogram==NULL)
    	return -1;
	for (int i = 0; i < 10; ++i)
		stats.histogram[i]=0;
	for (int i = 0; i < data.numStudents; i++)
	{
		int grade = data.students[i].grade;
		if (grade>=0 && grade <=9)
			stats.histogram[0]++;
		else if (grade>=10 && grade<=19)
			stats.histogram[1]++;
		else if (grade>=20 && grade<=29)
			stats.histogram[2]++;
		else if (grade>=30 && grade<=39)
			stats.histogram[3]++;
		else if (grade>=40 && grade<=49)
			stats.histogram[4]++;
		else if (grade>=50 && grade<=59)
			stats.histogram[5]++;
		else if (grade>=60 && grade<=69)
			stats.histogram[6]++;
		else if (grade>=70 && grade<=79)
			stats.histogram[7]++;
		else if (grade>=80 && grade<=89)
			stats.histogram[8]++;
		else if (grade>=90 && grade<=100)
			stats.histogram[9]++;
	}
	return 0;
}


int writeCSV(const char filename[], const Statistics& stats)
{
	ofstream out;
	out.open(statName(filename));	

	if (!out.is_open()) return -1;
	out << "Minimum: " << stats.minimum << endl << "Average: " << stats.average << endl;
	out << "Maximum: " << stats.maximum << endl << "Population Standard Deviation: " << stats.popStdDev << endl;
	out << "Sample Standard Deviation: " << stats.smplStdDev << endl << "Modes: ";
	
	for (int i = 0; i < stats.mode.numModes; i++)
	{
		out << stats.mode.modes[i];
		if (i<stats.mode.numModes-1)
			out << ", ";
	}
	out << "\nHistogram:" << endl << "[0-9]: " << stats.histogram[0] << endl << "[10-19]: " << stats.histogram[1] << endl;
	out << "[20-29]: " << stats.histogram[2] << endl << "[30-39]: " << stats.histogram[3] << endl << "[40-49]: " << stats.histogram[4] << endl;
	out << "[50-59]: " << stats.histogram[5] << endl << "[60-69]: " << stats.histogram[6] << endl << "[70-79]: " << stats.histogram[7] << endl;
	out << "[80-89]: " << stats.histogram[8] << endl << "[90-100]: " << stats.histogram[9];
	out.close();
	return 0;
}


#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {

	// Some test driver code here ....
	int minAcceptableID = 0;
	int maxAcceptableID = 2000000;

	Dataset data = {0};
	Rejects rejects = {0};
	Statistics stats = {0};

	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
	{
		std::cout << ".csv file could not be read" << std::endl;
	}

	if (computeStatistics(data, stats) < 0)
	{
		std::cout << "Stats could not be computed" << std::endl;
	}

	if (writeCSV(argv[1], stats) < 0)
	{
		std::cout << ".stat file could not be written" << std::endl;
	}

	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
	
	
	for (unsigned char i = 0; i < stats.mode.numModes; i++)
	{
		std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
	}

	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	

	return 0;
}

#endif
