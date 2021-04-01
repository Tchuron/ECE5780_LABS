#include "Task.hpp"

//std::shared_ptr<Task> Task::mPreviouslyExecuted;
Task* Task::mPreviouslyExecuted = nullptr;

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
  //std::cout << "constructor:" << mID << ", execT:" << mExecTime << ", execAl:" << mExecAlready << ", dedln:" << mDeadline << ", rel:" << mReleaseTime << ", periodic:" << mPeriodic << std::endl;
}

Task::Task(Task* other)
{
  mID = other->getID();
  mExecTime = other->getExecTime();
  mDeadline = other->getDeadline();
  mExecAlready = other->getExecAlready();
  mReleaseTime = other->getReleaseTime();
  mPeriodic = other->isPeriodic();
  //std::cout << "copy constructor " << mID << std::endl;
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

// intended for periodic tasks. aperiodic tasks would be in a different
// prioritized structure
int Task::getEdfPriority(int currentTime)
{
  if (!isReady(currentTime))
  {
    return INT_MAX;
  }
  return mDeadline; //return deadline
}

char Task::getID()
{
  return mID;
}

int Task::getReleaseTime()
{
  return mReleaseTime;
}

bool Task::isReady(int currentTime)
{
  //bool output = ((mReleaseTime <= currentTime) && (mExecTime > mExecAlready));
  //std::cout << mID << " ready@" << currentTime << ":" << output << std::endl;
  //std::cout << "vals:" << mID << ", execT:" << mExecTime << ", execAl:" << mExecAlready << ", dedln:" << mDeadline << ", rel:" << mReleaseTime << ", periodic:" << mPeriodic << std::endl;
  return (mReleaseTime <= currentTime && mExecTime > mExecAlready);
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

// returns whether a pre-emption occured
bool Task::execute(int currentTime, std::ofstream* fileOut)
{
  bool returnVal = false;
  std::cout << "[" << currentTime << "ms] : " << mID << std::endl;
  *fileOut << "[" << currentTime << "ms] : " << mID << std::endl;
  mExecAlready++;
  if (mPreviouslyExecuted != nullptr &&
      mPreviouslyExecuted->getID() != mID &&
      !mPreviouslyExecuted->isFinished())
  {
    std::cout << "Task " << mID << " pre-empted " << mPreviouslyExecuted->getID() << std::endl;
    *fileOut << "Task " << mID << " pre-empted " << mPreviouslyExecuted->getID() << std::endl;
    returnVal = true;
  }
  if (mExecAlready >= mExecTime) // check if finishing
  {
    if (mPeriodic)
    {
      periodicPushForward();
    }
  }
  mPreviouslyExecuted = this; // update the static previous task holder
  return returnVal;
}
