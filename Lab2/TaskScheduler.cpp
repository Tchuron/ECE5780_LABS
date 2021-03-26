#include "TaskScheduler.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <charconv> 
#include <ctype.h>

TaskScheduler::TaskScheduler(std::string inFile, std::string outFile)
{
	// Open Files
	std::ifstream fileInStream (inFile);;
	std::ofstream  fileOutStream (outFile);
	
	int numTasks;
	int numAperiodic;
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
			fileInStream >> idName; 				// Parse the ID of each task from the input file
			if (isdigit(idName[0])){ 				// Check to see if the id name is a number
				numAperiodic = std::stoi(idName); 	// If it is parse into the number of aperiodic tasks
				fileInStream >> idName; 			// Get the next value from the file for the id name
				std::cout << "number of aperiodic tasks: " << numAperiodic << std::endl;
			}
			fileInStream >> execTime >> tempString >> period; 
			std::cout << "Created new task. ID: " << idName << " ExecTime: " << execTime << " Period: " << period << std::endl;
			//TaskEDF newTask = new TaskEDF(id, execTime, period);
			//mTasks.push(newTask);
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
