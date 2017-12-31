//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

//////////////////////////////////////////////////////////////
//
// #includes for local testing only
//


#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// Enums and structs for use in assignment 

#ifndef MARMOSET_TESTING
enum COURSE
{
	CHE102,
	MATH115,
	MATH117,
	ECE105,
	ECE150,
	ECE190,
	Null
};

struct Assignment
{
	COURSE course;       
	int    assnNum;      // Assignment number
	int    dueMonth;     // 1-12
	int    dueDay;       // 1-31
	char*  description;  // Assignment description
};

#endif


//////////////////////////////////////////////////////////////
//
// Class declaration; modify but do not remove
							 
class HomeworkQueue 
{
public:
    bool                enqueue(const Assignment& assignment);
    const Assignment*   dequeue();
    int                 daysTillDue(const COURSE course);
    const Assignment*   dueIn(const int numDays);


    HomeworkQueue();    //constructor
    ~HomeworkQueue();   //destructor
private:
    // It is up to you what you store here
};


//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool HomeworkQueue::enqueue(const Assignment& assignment)
{
	return false;
}

const Assignment* HomeworkQueue::dequeue()
{
	return NULL;
}

int HomeworkQueue::daysTillDue(const COURSE course)
{
	return -1;
}

const Assignment* HomeworkQueue::dueIn(const int numDays)
{
	return NULL;
}

HomeworkQueue::HomeworkQueue()
{

}

HomeworkQueue::~HomeworkQueue()
{
	//Please clean up
}



		

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[]) 
{
	//formatting
	std::cout << std::endl;

	HomeworkQueue hwq;

	char boring[] = "Something something solubility something something gases something";

	Assignment someAssignment = 
	{
		.course = CHE102,
		.assnNum = 1000000,
		.dueMonth = 12,
		.dueDay = 4,
		.description = boring
	};

	if(!hwq.enqueue(someAssignment))
	{
		std::cout << "enqueue() unsuccessful" << std::endl;
	}
	else
	{
		std::cout << "enqueue() successful" << std::endl;
	}

	const Assignment* assnInTheQueue = hwq.dequeue();

	if (!assnInTheQueue)
	{
		std::cout << "dequeue() unsuccessful" << std::endl;

	}
	else 
	{
		std::cout << "dequeue() successful" << std::endl;
	}

	//formatting
	std::cout << std::endl;

    return 0;
}
#endif
