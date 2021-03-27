#include <memory>
#include <climits>
#include <iostream>
class Task
{
  public:
    // deadline is the release time for aperiodic and period for periodic
    Task(char id, int execTime, int deadline, bool periodic);
    Task(Task* other);
    bool operator==(const Task& other);
    bool operator!=(const Task& other);
    bool isPeriodic();
    int getExecTime();
    int getExecAlready();
    int getDeadline();// for EDF scheduling
    int getRmaPriority(int currentTime); // for RMA scheduling
    char getID();
    bool isReady(int currentTime);
    bool isFinished();
    void execute(int currentTime);
  private:
    void periodicPushForward();
    char mID;
    int mExecTime;
    int mExecAlready;
    int mReleaseTime;
    int mDeadline;
    bool mPeriodic;
    Task* mPreviouslyExecuted = nullptr;
};
