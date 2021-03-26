#include <iostream>
#include <string>
#include "TaskScheduler.hpp"

void printHelp()
{
	std::cout << "Help information" << std::endl;
	printf("USAGE: ./Scheduler <IN file> <OUT file>");
	printf("<IN file> is the input file to be processed\n");
	printf("<OUT file> is the output file to be generated\n");
  exit(1);
}
int main(int argc, char **argv)
{
	
	
	if (argc < 3) {
		printHelp();
	}
	else{
		std::string inPath = argv[1];
		std::string outPath = argv[2];
		TaskScheduler* ts = new TaskScheduler(inPath, outPath);
	}
}
