#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <memory>
#include <climits>
#include "Task.hpp"
class TaskScheduler
{
  public:
    TaskScheduler(std::string inFile, std::string outFile);
    void runScheduleRMA();
    void runScheduleEDF();
	void printReport();
	int getEdfMissed();
	int getEdfPreem();
	int getRmaMissed();
	int getRmaPreem();
	~TaskScheduler();
  private:
    int mTimeLimit; // the simulation time
    int mTime = 0;
    std::vector<std::shared_ptr<Task>> mLoadedTasks;
    std::ofstream mScheduleOutput;
	int edfNumDeadlineMiss = 0;
	int edfNumPreemptions = 0;
	int rmaNumDeadlineMiss = 0;
	int rmaNumPreemptions = 0;

	
};
