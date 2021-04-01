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
	int getEdfMissed();
	int getEdfPreem();
	int getRmaMissed();
	int getRmaPreem();
  private:
    int mTimeLimit; // the simulation time
    int mTime = 0;
    std::vector<std::shared_ptr<Task>> mLoadedTasks;
    std::ofstream mScheduleOutput;
	int EdfNumDeadlineMiss = 0;
	int EdfNumPreemptions = 0;
	int RmaNumDeadlineMiss = 0;
	int RmaNumPreemptions = 0;
	
};
