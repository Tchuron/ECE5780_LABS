#include <iostream>
#include <string>
#include "TaskScheduler.hpp"

void printHelp()
{
  std::cout << "Help information" << std::endl;
  exit(1);
}
int main(int argc, char** argv)
{
  if (argc < 3) printHelp();
  std::string inPath = argv[1];
  std::string outPath = argv[2];
  TaskScheduler* ts = new TaskScheduler(inPath, outPath);
}
