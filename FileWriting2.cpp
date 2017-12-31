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

// Func08RjectedLines.py and Func10NoExtension.py are checking for the case when there is no extension 
// given to filename (i.e filename = "text")
// Make sure you are only rejecting a single line if it has invalid characters, not the whole file.
/*
	"Prior to writing to either change the .csv to a .stat, or add the .stat if it doesn't have any extension."
	Or leave it if it already has a ".stat"
	And never accept a filename with more than one "." in the name, such as "foo.bat.csv" or "foo..csv"
	Prior to writing to either change the .csv to a .stat, or add the .stat if it doesn't have any extension.
*/
// For the Func09ChangeExtension test, are the extensions supposed to be case sensitive? Also, if a csv
// file is called .csv, are we expected to know to add a second .csv on top of that? Can't test each
// possibility with a release test everytime, already used 3. :/
/*
Yes to case sensitivity, as this your code is tested in Linux. There are 2 cases to consider:
If the extension is .csv, just read from the file with that exact name, but change the .csv termination 
to .stat for the output file
If there is no extension, terminate with .csv in order to read, and terminate with .stat to write. 
There shouldn't be any "double extensions", like .csv on top of .csv
*/
/*
Func08RejectedLines.py and Func09ChangeExtension.py
What are these testing for?
I'm guessing change extension is testing for wrong extensions. But the assignment description says the 
file name entered will either have nothing after the file name or ".csv"
And guessing rejected lines checks to make sure we stored the correct line numbers in the rejects 
pointer? I did this but not passing.

For rejected lines there are two cases where you have to reject lines: 
1. Multiple commas in a line.
2. Whitespace in the middle of the student number or student grade. (Only trailing and leading whitespace should be allowed)
I also talked to one of the TAs and they mentioned that they aren't checking for invalid characters this time.
*/



/*
A loaded line may be one with just numbers no commas, but still less than the 
length of line (source: fixed that and passed the test)
*/

// As the lab states that the only two valid cases are no extension and .csv, if you 
// have another extension you should reject it and return -1.

/*
Func01Average.py
Does your code have the same amount of error checking as the file reading/statistics/mode assignment if not 
more? I just ported my code over and have not encountered any issues
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

/*
FileWriting--missing data Func14
I failed on this test case for FileWriting. I cannot figure out which part of the data 
can be missing. Does it mean that the file can be empty or one student only has grade and no studentID?

It's the latter of the two
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
			{seenDot = true;break;}	
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
  	rejects.rejects = new int[rejectSize];

  	for (int i = 0; i < rejectSize; ++i)
  	{
  		rejects.rejects[i]=0;
  	}

  	rejects.numRejects = 0;
  	data.students = new Student[101];
  	
  	data.numStudents=0;
  	for (int i = 0; i < 101; i++)
  	{
  		data.students[i].studentID = 0;
  		data.students[i].grade = 0;
  	}
  	while (!done) 
  	{ 
  		//	cout << "# of rejects so far " << rejects.numRejects << endl;
  		//*********************************************************************
  		// CURRENT LINE

		/*
		Func08RejectedLines.py and Func09ChangeExtension.py
		What are these testing for?
		I'm guessing change extension is testing for wrong extensions. But the assignment description says the 
		file name entered will either have nothing after the file name or ".csv"
		
		And guessing rejected lines checks to make sure we stored the correct line numbers in the rejects 
		pointer? I did this but not passing.
		
		For rejected lines there are two cases where you have to reject lines: 
		1. Multiple commas in a line.
		2. Whitespace in the middle of the student number or student grade. (Only trailing and leading whitespace should be allowed)
		I also talked to one of the TAs and they mentioned that they aren't checking for invalid characters this time.
		*/


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

    	while (line[i]!=0 && line[i]!='\r') // goes till no more lines, SKIPS \r lines
    	{
    		if (rejekt) 
    		{
    			//cout << "broke the line" << endl;
    			break;
    		}
	    	 
    		else if (line[i]==',' && comma) // if multiple commas, its a reject
	    	{
	    		rejects.rejects[rejects.numRejects++] = fileLineNumber;
	    		if (rejects.numRejects>=rejectSize) 
	    			return -1;
	    		rejekt=true;
	    		//cout << "line " << fileLineNumber << " rejected: comma appearing twice" << endl;
	    		continue;
	    	}
	    	else if (line[i]==',') comma=true;

	    	 // if its whitespace or tabs, not reject just continue
    		else if (line[i]==' ' || line[i]=='\t');
	    	
	    	  // if its a number
    		else if (line[i]<='9' && line[i]>='0')
    		{  
	    	    // if comma didn't occur yet, we're reading in student ID
    			if (!comma)
    			{
    				if (studentID) // in the case where theres [valid student id]    [valid student id]
    				{
    					rejects.rejects[rejects.numRejects++] = fileLineNumber;
    					if (rejects.numRejects>=rejectSize)
    						return -1;
    					rejekt=true;
    					//cout << "line " << fileLineNumber << " rejected: studentID appearing twice" << endl;
    					continue;
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
	    	      		// as soon as a non-number character appears, check if minAcceptableID<studentID<maxAcceptableID
    					if (studentID<minAcceptableID || studentID>maxAcceptableID)
    					{
	    	        	// if studentID invalid, reject and break
    						rejects.rejects[rejects.numRejects++] = fileLineNumber;
    						if (rejects.numRejects>=rejectSize)
    							return -1;
    						rejekt=true;
    						//cout << "line " << fileLineNumber << " rejected: studentID invalid bounds" << endl;
    						continue;
    					}
    					else
    						data.students[fileLineNumber-1].studentID = studentID;
    				}
    			}
    			else // must be reading grade, cuz hasnt been rejected, and a comma already occurred
    			{
    				if (grade) // in the case where theres [valid grade]    [valid grade]
    				{
    					rejects.rejects[rejects.numRejects++] = fileLineNumber;
    					if (rejects.numRejects>=rejectSize)
    						return -1;
    					rejekt=true;
    					//cout << "line " << fileLineNumber << " rejected: grade appearing twice" << endl;
    					continue;
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
	    	      		// as soon as non-number character appears, check if 0<=grade<=100
    					if (grade>=0 && grade <= 100)
    						data.students[fileLineNumber-1].grade = grade;
	    	      		else // try commenting this out if shit dont work
	    	      		{
	    	      		  // if grade invalid, reject and break
	    	      			rejects.rejects[rejects.numRejects++] = fileLineNumber;
	    	      			if (rejects.numRejects>=rejectSize)
	    	      				return -1;
	    	      			rejekt=true;
	    	      			//cout << "line " << fileLineNumber << " rejected: grade invalid bounds" << endl;
	    	      			continue;
	    	      		}
	    	  		}
	    	  	}
	    	}
	    	
	    	else // if its any other character, reject the line not the file necessarily
	    	{
	    		invalidCharSeen=true;
	    		rejects.rejects[rejects.numRejects++] = fileLineNumber;
	    		if (rejects.numRejects>=rejectSize)
	    			return -1;
	    		rejekt=true;
	    		//cout << "line " << fileLineNumber << " rejected: invalid character appeared" << endl;
	    		continue;
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
	    	rejects.rejects[rejects.numRejects++] = fileLineNumber;
			if (rejects.numRejects>=rejectSize)
				return -1;
			rejekt=true;
			//cout << "line " << fileLineNumber << " rejected: badline complex" << endl;
	    }

	}

	data.numStudents = (fileLineNumber - rejects.numRejects -1);
	//cout << "data.numStudents at the end = " << data.numStudents << endl;

	//cout << "rejects.numRejects at the end = " << rejects.numRejects << endl;
	return rejects.numRejects;
}

int computeStatistics(Dataset& data, Statistics& stats)
{
	float s1 = 0;
	float s2 = 0;

	int srtd[data.numStudents];
	for (int i = 0; i <= data.numStudents; i++)
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
	
	for (int i = 0; i < data.numStudents; i++){
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
	// cout the file name
	out.open(statName(filename)); // this should make the file gud
	// cout the flie name now, compare see if its right
	

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
