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
	int execTime;
	int period;
	int id = 0;
  bool aperiodicSection = false;
	std::string idName;
	std::string input;
	std::string tempString;
	
	// Parse the first two variables from the input file
	fileInStream >> numTasks;
	fileInStream >> mTimeLimit;
	
	// Print the variables just parsed
	std::cout << "NumTasks: " << numTasks << " simTimeMs: " << mTimeLimit << std::endl;
	if (fileInStream.is_open()){
		while (fileInStream.eof() == false) // Go through each line of the file
		{
			fileInStream >> idName; 				// Parse the ID of each task from the input file
			if (isdigit(idName[0])){ 				// Check to see if the id name is a number
				numAperiodic = std::stoi(idName); 	// If it is parse into the number of aperiodic tasks
				fileInStream >> idName; 			// Get the next value from the file for the id name
				std::cout << "number of aperiodic tasks: " << numAperiodic << std::endl;
        aperiodicSection = true;
			}
			fileInStream >> execTime >> tempString >> period; 
			std::cout << "Created new task. ID: " << idName << " ExecTime: " << execTime << " Period: " << period << std::endl;
      mLoadedTasks.push_back(std::make_shared<Task>(idName[0], execTime, period, !aperiodicSection));
			//TaskEDF newTask = new TaskEDF(id, execTime, period);
			//mTasks.push(newTask);
		}
	}
	else{ // Print an error message if the input file did not open correctly
		std::cout << "input file did not open" << std::endl;
	}
	
	fileInStream.close();
}

void TaskScheduler::runScheduleRMA()
{
  std::vector<std::shared_ptr<Task>> rmaTasks = {};
  // copy the tasks into the two queues
  for (int i = 0; i < mLoadedTasks.size(); i++)
  {
    //Task temp = *mLoadedTasks[i];
    //rmaTasks.push_back(std::make_shared<Task>(mLoadedTasks[i].get()));
    std::shared_ptr<Task> copyTask = std::make_shared<Task>(mLoadedTasks[i].get());
    rmaTasks.push_back(copyTask);
  }

  while (mTime < mTimeLimit && rmaTasks.size() > 0)
  {
    // check which periodic task is ready and has shortest period, if any
    std::shared_ptr<Task> bestPeriodicTask;
    std::shared_ptr<Task> bestAperiodicTask;
    int bestPeriodicTaskPriority = INT_MAX;
    int bestAperiodicTaskPriority = INT_MAX;
    for (int i = 0; i < rmaTasks.size(); i++)
    {
      // look for the highest priority ready periodic task
      if (rmaTasks[i]->isPeriodic())
      {
        if(rmaTasks[i]->isReady(mTime) && rmaTasks[i]->getRmaPriority(mTime) < bestPeriodicTaskPriority)
        {
          //std::cout << "use count before " << rmaTasks[i].use_count() << std::endl;
          bestPeriodicTask = rmaTasks[i];
          //std::cout << "use count after " << rmaTasks[i].use_count() << std::endl;
          bestPeriodicTaskPriority = rmaTasks[i]->getRmaPriority(mTime);
        }
      }
      else // the task is aperiodic
      {
        if(rmaTasks[i]->isReady(mTime) && rmaTasks[i]->getDeadline() < bestAperiodicTaskPriority)
        {
          bestAperiodicTask = rmaTasks[i];
          bestAperiodicTaskPriority = rmaTasks[i]->getDeadline();
        }
      }
      // check for any late tasks
      if (rmaTasks[i]->getDeadline() == mTime)
      {
        std::cout << "Task " << rmaTasks[i]->getID() << " missed deadline." << std::endl;
      }
    }

    if (bestPeriodicTask) // if we found a ready periodic task
    {
      //std::cout << "exectask: " << bestPeriodicTask << std::endl;
      bestPeriodicTask->execute(mTime);
    }
    else if (bestAperiodicTask)
    {
      bestAperiodicTask->execute(mTime);
    }
    mTime++;
  }
}

void TaskScheduler::runScheduleEDF()
{
	std::cout << "Nothing here" << std::endl;
}
