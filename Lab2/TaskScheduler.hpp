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
  private:
    int mTimeLimit; // the simulation time
    int mTime = 0;
    std::vector<std::shared_ptr<Task>> mLoadedTasks;
    std::ofstream mScheduleOutput;
	
};
