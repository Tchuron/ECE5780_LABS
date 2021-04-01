#include <iostream>
#include <string>
#include "TaskScheduler.hpp"
using namespace std;

void printHelp()
{	
	std::cout << "Help information" << std::endl;
	exit(1);
}
int main(int argc, char** argv)
{
	int EdfNumDeadlineMiss = 0;
	int EdfNumPreemptions = 0;
	int RmaNumDeadlineMiss = 0;
	int RmaNumPreemptions = 0;
	
	//Process command line arguments
	if (argc < 3) { //print instructions if the user did not enter the file names correctly
		
		std::printf("USAGE: %s <IN file> <OUT file> \n",argv[0]);
		std::printf("<IN file> is the input file to be processed\n");
		std::printf("<OUT file> is the output file to be generated\n");printHelp(); 	
		return 0; //end program
	}		
	
	std::string inPath = argv[1];
	std::string outPath = argv[2];
	TaskScheduler* ts = new TaskScheduler(inPath, outPath); //pass file names to Task Scheduler
	cout << "running RMA schedule: " << endl;
	ts->runScheduleRMA();
	cout << "running EDF schedule: " << endl;
	ts -> runScheduleEDF();
	
	//print report on the number of missed deadlines and preemptions
	EdfNumDeadlineMiss = ts -> getEDFMissed();
	EdfNumPreemptions = ts -> getEdfPreem();
	RmaNumDeadlineMiss = ts -> getRmaMissed();
	RmaNumPreemptions = ts -> getRmaPreem();
	
	cout << "End of Program Report" << endl;
	cout << "_______________________________________"<< endl;
	cout << "# RMA Deadlines Missed: " << RmaNumDeadlineMiss << endl;
	cout << "# RMA Tasks Preempted:  " << RmaNumPreemptions << endl;
	cout << "# EDF Deadlines Missed: " << EdfNumDeadlineMiss << endl;
	cout << "# EDF Tasks Preempted:  " << EdfNumPreemptions << endl;
	
	return 1;
} // End of main function
