#include <fstream>
#include <iostream>
class TaskScheduler
{
  public:
    TaskScheduler(std::string inFile, std::string outFile);
    void runSchedule();
  private:
    //std::priority_queue<Task> mTasks;
    //std::priority_queue<Task> mReadyTasks;
    std::ofstream mScheduleOutput;
};
