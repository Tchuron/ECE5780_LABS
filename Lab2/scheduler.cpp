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
  ts->runScheduleRMA();
	
	return 1;
} // End of main function
