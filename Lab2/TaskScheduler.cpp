#include "TaskScheduler.hpp"
#include <string>
#include <fstream>
#include <iostream>

TaskScheduler::TaskScheduler(std::string inFile, std::string outFile)
{
	// Open Files
	std::ifstream fileInStream (inFile);;
	std::ofstream  fileOutStream (outFile);
	
	int numTasks;
	int simTimeMs;
	int execTime;
	int period;
	int id = 0;
	std::string idName;
	std::string input;
	std::string tempString;
	
	// Parse the first two variables from the input file
	fileInStream >> numTasks;
	fileInStream >> simTimeMs;
	
	// Print the variables just parsed
	std::cout << "NumTasks: " << numTasks << " simTimeMs: " << simTimeMs << std::endl;
	if (fileInStream.is_open()){
		while ((fileInStream.eof() == false) && id < 15) // Go through each line of the file
		{
			fileInStream >> idName;
			
			fileInStream >> execTime >> tempString >> period; 
			std::cout << "Created new task. ID: " << idName << " ExecTime: " << execTime << " Period: " << period << std::endl;
			//TaskEDF newTask = new TaskEDF(id, execTime, period);
			//mTasks.push(newTask);
			//std::cout << "parsed only " << parsedFields << " fields." << std::endl;
			id++; // increment id
			//std::cout << id << std::endl;
		}
	}
	else{ // Print an error message if the input file did not open correctly
		std::cout << "input file did not open" << std::endl;
	}
	
	fileInStream.close();
	fileOutStream.close();
}

void TaskScheduler::runSchedule()
{
	std::cout << "Nothing here" << std::endl;
}
