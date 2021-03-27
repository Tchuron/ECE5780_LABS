#include "Task.hpp"

//std::shared_ptr<Task> Task::mPreviouslyExecuted;

Task::Task(char id, int execTime, int deadline, bool periodic)
{
  std::cout << "OG contstructor: " << id << std::endl;
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

Task::Task(Task* other)
{
  std::cout << "copy contstructor: " << other->getID() << std::endl;
  mID = other->getID();
  mExecTime = other->getExecTime();
  mDeadline = other->getDeadline();
  mExecAlready = other->getExecAlready();
  mPeriodic = other->isPeriodic();
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

int Task::getExecAlready()
{
  return mExecAlready;
}

int Task::getExecTime()
{
  return mExecTime;
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
  return (mReleaseTime <= currentTime && mExecTime > mExecAlready);
}

void Task::periodicPushForward()
{
  std::cout << "Pushing back periodic task " << mID << std::endl;
  if (!mPeriodic)
    std::cout << "Problem: aperiodic task where it should not be." << std::endl;
  mExecAlready = 0;
  int period = mDeadline - mReleaseTime;
  mReleaseTime = mDeadline;
  mDeadline = mReleaseTime + period;
}

bool Task::isFinished()
{
  if (mExecAlready >= mExecTime)
  {
    std::cout << "task " << mID << " is finished" << std::endl;
  }
  return mExecAlready >= mExecTime;
}

void Task::execute(int currentTime)
{
  std::cout << "Task " << mID << " executed time :" << currentTime << std::endl;
  mExecAlready++;
  if (mPreviouslyExecuted != nullptr &&
      mPreviouslyExecuted->getID() != mID &&
      !mPreviouslyExecuted->isFinished())
  {
    std::cout << "Task " << mID << " has pre-empted " << mPreviouslyExecuted->getID() << std::endl;
  }
  if (mExecAlready >= mExecTime) // check if finishing
  {
    std::cout << "Task " << mID << " is done." << std::endl;
    if (mPeriodic)
    {
      periodicPushForward();
    }
  }
  //std::cout << "this: " << this << std::endl;
  //std::cout << "resetting previous smart pointer" << std::endl;
  //std::cout << "use count 1: " << mPreviouslyExecuted.use_count() << std::endl;
  mPreviouslyExecuted = this;
  //mPreviouslyExecuted.reset(this); // update previously executed task
  //std::cout << "use count 2: " << mPreviouslyExecuted.use_count() << std::endl;
}
