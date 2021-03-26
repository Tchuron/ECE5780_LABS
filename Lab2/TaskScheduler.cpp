#include "TaskScheduler.hpp"
#include <string>
#include <fstream>
#include <iostream>

TaskScheduler::TaskScheduler(std::string inFile, std::string outFile)
{
	// Open Files
	std::ifstream fileInStream (inFile);;
	std::ofstream  fileOutStream (outFile);

	if (!fileInStream.is_open()) // Print an error message if the input file did not open correctly
	{
		std::cout << "input file did not open" << std::endl;
	}
	
	int numTasks = 0;
	int simTimeMs = 0;
	int execTime;
	int period;
	int execTime = 0;
	int period = 0;
	int id = 0;
	std::string line;
	std::getline(fileInStream, line);
	std::string idName = "";
	std::string tempString;
	
	// Parse the first two variables from the input file
	fileInStream >> numTasks;
	fileInStream >> simTimeMs;
	
	// Print the variables just parsed
	std::cout << "NumTasks: " << numTasks << " simTimeMs: " << simTimeMs << std::endl;

	while (!fileInStream.eof() && id < 20)
	{

		//int parsedFields = sscanf(line.c_str(), "%c, %d, %d", &tempString, &execTime, &period);

		//Parse data from the input file
		fileInStream >> numTasks;
		fileInStream >> execTime;
			
		fileInStream >> idName; // = std::string(tempString);
		fileInStream >> execTime;
		fileInStream >> period;
			
		std::cout << "Created new task. ID: " << tempString << " ExecTime: " << execTime << " Period: " << period << std::endl;
		//TaskEDF newTask = new TaskEDF(id, execTime, period);
		//mTasks.push(newTask);
		//std::cout << "parsed only " << parsedFields << " fields." << std::endl;
		id++; // increment id
	}
}

void TaskScheduler::runSchedule()
{
	std::cout << "Nothing here" << std::endl;
}
