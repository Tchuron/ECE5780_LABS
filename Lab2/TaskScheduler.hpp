#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <memory>
#include "Task.hpp"
class TaskScheduler
{
  public:
    TaskScheduler(std::string inFile, std::string outFile);
    void runSchedule();
  private:
    std::vector<std::shared_ptr<Task>> mLoadedTasks;
    std::ofstream mScheduleOutput;
};
