#include "Task.hpp"

Task::Task(char id, int execTime, int deadline, bool periodic)
{
  mID = id;
  mExecTime = execTime;
  mExecAlready = 0;
  mPeriodic = periodic;
  if (periodic)
  {
    mReleaseTime = 0;
    mDeadline = deadline;
  }
  else
  { //aperiodic
    mReleaseTime = deadline;
    mDeadline = deadline + 500; // implicit 500ms deadline
  }
}

bool Task::operator==(const Task& other)
{
  return this->mID == other.mID;
}

bool Task::operator!=(const Task& other)
{
  return *this == other;
}

bool Task::isPeriodic()
{
  return mPeriodic;
}

int Task::getDeadline()
{
  return mDeadline;
}

// intended for periodic tasks. aperiodic tasks would be in a different
// prioritized structure
int Task::getRmaPriority(int currentTime)
{
  if (!isReady(currentTime))
  {
    return INT_MAX;
  }
  if (!mPeriodic)
    std::cout << "Problem: aperiodic task where it should not be." << std::endl;
  return mDeadline - mReleaseTime; // the period
}

char Task::getID()
{
  return mID;
}

bool Task::isReady(int currentTime)
{
  return (mReleaseTime <= currentTime && mExecTime < mExecAlready);
}

void Task::periodicPushForward()
{
  if (!mPeriodic)
    std::cout << "Problem: aperiodic task where it should not be." << std::endl;
  mExecAlready = 0;
  int period = mDeadline - mReleaseTime;
  mReleaseTime = mDeadline;
  mDeadline = mReleaseTime + period;
}

bool Task::isFinished()
{
  return mExecAlready >= mExecTime;
}

void Task::execute(int currentTime)
{
  mExecAlready++;
  if (mPreviouslyExecuted &&
      *mPreviouslyExecuted != *this &&
      !mPreviouslyExecuted->isFinished())
  {
    std::cout << "Task " << mID << " has pre-empted " << mPreviouslyExecuted->getID() << std::endl;
  }
  if (mExecAlready >= mExecTime) // check if finishing
  {
    std::cout << "Task " << mID << " is done." << std::endl;
  }
  else
  {
    if (currentTime == mDeadline) // we are currently passing deadline
    {
      std::cout << "Task " << mID << " missed deadline." << std::endl;
    }
  }
  mPreviouslyExecuted.reset(this); // update previously executed task
}
