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
	mScheduleOutput.open(outFile);
	
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
      else
      {
			fileInStream >> execTime >> tempString >> period; 
			std::cout << "Created new task. ID: " << idName << " ExecTime: " << execTime << " Period: " << period << std::endl;
			mLoadedTasks.push_back(std::make_shared<Task>(idName[0], execTime, period, !aperiodicSection));
			//TaskEDF newTask = new TaskEDF(id, execTime, period);
			//mTasks.push(newTask);
      }
		}
	}
	else{ // Print an error message if the input file did not open correctly
		std::cout << "input file did not open" << std::endl;
	}
	fileInStream.close();
}

void TaskScheduler::runScheduleRMA() //RMA Task Scheduler
{
	mTime = 0;
  std::vector<std::shared_ptr<Task>> rmaTasks = {};
  // copy the tasks into the two queues
  
  for (int i = 0; i < mLoadedTasks.size(); i++)
  {
    std::shared_ptr<Task> copyTask = std::make_shared<Task>(mLoadedTasks[i].get());
    rmaTasks.push_back(copyTask);
  }
  	std::cout << std::endl <<"running RMA schedule: " << std::endl << std::endl;
	mScheduleOutput << std::endl << "running RMA schedule: " << std::endl << std::endl;

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
          bestPeriodicTask = rmaTasks[i];
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
        if (rmaTasks[i]->isReady(mTime))
          std::cout << "Task " << rmaTasks[i]->getID() << " missed deadline" << std::endl;
		  mScheduleOutput << "Task " << rmaTasks[i]->getID() << " missed deadline" << std::endl;
		  rmaNumDeadlineMiss++;
      }
    }

    if (bestPeriodicTask) // if we found a ready periodic task
    {
      bool temp = bestPeriodicTask->execute(mTime, &mScheduleOutput);
      if (temp) rmaNumPreemptions++;
    }
    else if (bestAperiodicTask)
    {
      bool temp = bestAperiodicTask->execute(mTime, &mScheduleOutput);
      if (temp) rmaNumPreemptions++;
    }
    else
    {
      std::cout << "[" << mTime << "ms] : NONE" << std::endl;
	  mScheduleOutput << "[" << mTime << "ms] : NONE" << std::endl;
    }
    mTime++;
  }
}
//////////////////////////////////
//EDF Task Scheduler
//////////////////////////////////
void TaskScheduler::runScheduleEDF()
{
	mTime = 0;
	std::vector<std::shared_ptr<Task>> edfTasks = {};

	
	for (int i = 0; i < mLoadedTasks.size(); i++) // Copy the tasks into the two queues
	{	
		std::shared_ptr<Task> copyTask = std::make_shared<Task>(mLoadedTasks[i].get());
		edfTasks.push_back(copyTask);
	}	
	std::cout << std::endl <<"running EDF schedule: " << std::endl << std::endl;
	mScheduleOutput << std::endl << "running EDF schedule: " << std::endl << std::endl;
	while (mTime < mTimeLimit && edfTasks.size() > 0)
	{
		// Check which task is ready and has the closest deadline.
		std::shared_ptr<Task> bestTask;
		int bestTaskPriority = INT_MAX;	
		for (int i = 0; i < edfTasks.size(); i++)
		{
			// Look for the highest priority ready task
			if(edfTasks[i]->isReady(mTime) && edfTasks[i]->getEdfPriority(mTime) < bestTaskPriority)
			{
				bestTask = edfTasks[i];
				bestTaskPriority = edfTasks[i]->getEdfPriority(mTime);
				//bestTaskPriority = edfTasks[i]->getDeadline();
			}
			if (edfTasks[i]->getDeadline() == mTime)// Check for late tasks
			{
				if (edfTasks[i]->isReady(mTime)){
				std::cout << "Task " << edfTasks[i]->getID() << " missed deadline" << std::endl;
				mScheduleOutput << "Task " << edfTasks[i]->getID() << " missed deadline" << std::endl;
				edfNumDeadlineMiss++; //increment the number of deadlines missed
				}
			}


		}
		// if we found a readytask
		if (bestTask) // if we found a ready periodic task
		{
			bool temp = bestTask->execute(mTime, &mScheduleOutput);
			if (temp) edfNumPreemptions++;
		}
		else
		{	//no task being executed. Print to output file
			std::cout << "[" << mTime << "ms] : NONE" << std::endl;
			mScheduleOutput << "[" << mTime << "ms] : NONE" << std::endl;
		}
		mTime++;
	}
	std::cout << "Nothing here" << std::endl;
}

int TaskScheduler::getEdfMissed(){
	return edfNumDeadlineMiss;
}
int TaskScheduler::getEdfPreem(){
	return edfNumPreemptions;
}
int TaskScheduler::getRmaMissed(){
	return rmaNumDeadlineMiss;
}
int TaskScheduler::getRmaPreem(){
	return rmaNumPreemptions;
}
void TaskScheduler::printReport(){
	//print report on the number of missed deadlines and preemptions
	edfNumDeadlineMiss = this -> getEdfMissed();
	edfNumPreemptions  = this -> getEdfPreem();
	rmaNumDeadlineMiss = this -> getRmaMissed();
	rmaNumPreemptions  = this -> getRmaPreem();
	// Print summary report to terminal 
	std::cout << " End of Program Report" << std::endl;
	std::cout << "_______________________________________"<< std::endl;
	std::cout << "# RMA Deadlines Missed: " << rmaNumDeadlineMiss << std::endl;
	std::cout << "# RMA Tasks Preempted:  " << rmaNumPreemptions << std::endl;
	std::cout << "# EDF Deadlines Missed: " << edfNumDeadlineMiss << std::endl;
	std::cout << "# EDF Tasks Preempted:  " << edfNumPreemptions << std::endl;
	// Print summary report to output file
	mScheduleOutput << " End of Program Report" << std::endl;
	mScheduleOutput << "_______________________________________"<< std::endl;
	mScheduleOutput << "# RMA Deadlines Missed: " << rmaNumDeadlineMiss << std::endl;
	mScheduleOutput << "# RMA Tasks Preempted:  " << rmaNumPreemptions << std::endl;
	mScheduleOutput << "# EDF Deadlines Missed: " << edfNumDeadlineMiss << std::endl;
	mScheduleOutput << "# EDF Tasks Preempted:  " << edfNumPreemptions << std::endl;
}


TaskScheduler::~TaskScheduler(){

	//close output file
	mScheduleOutput.close();
}
	

