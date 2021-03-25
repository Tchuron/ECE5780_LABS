#include "TaskScheduler.hpp"

TaskScheduler::TaskScheduler(std::string inFile, std::string outFile)
{
  std::ifstream fileInStream(inFile.c_str(), std::ifstream::in);
  mScheduleOutput.open(outFile.c_str(), std::ofstream::out);
  if (!fileInStream.is_open())
  {
    std::cout << "input file did not open" << std::endl;
  }
  int numTasks = 0;
  int simTimeMs = 0;
  fileInStream >> numTasks;
  fileInStream >> simTimeMs;
  std::cout << "NumTasks: " << numTasks << " simTimeMs: " << simTimeMs << std::endl;
  int id = 0;
  while (!fileInStream.eof() && id < 20)
  {
    std::string line;
    std::getline(fileInStream, line);
    int execTime = 0;
    int period = 0;
    std::string idName = "";
    char tempString;
    int parsedFields = sscanf(line.c_str(), "%c, %d, %d", &tempString, &execTime, &period);
    if (parsedFields == 3)
    {
    //idName = std::string(tempString);
    //fileInStream >> idName;
    //fileInStream >> execTime;
    //fileInStream >> period;
    std::cout << "Created new task. ID: " << tempString << " ExecTime: " << execTime << " Period: " << period << std::endl;
    //TaskEDF newTask = new TaskEDF(id, execTime, period);
    //mTasks.push(newTask);
    }
    else
    {
      std::cout << "did not parse the fields this time. ID: " << id << std::endl;
      std::cout << "parsed only " << parsedFields << " fields." << std::endl;
    }
    id++;
  }
}

void TaskScheduler::runSchedule()
{
  std::cout << "Nothing here" << std::endl;
}
