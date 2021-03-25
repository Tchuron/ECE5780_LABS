class Task
{
  public:
    // deadline is the release time for aperiodic and period for periodic
    Task(char id, int execTime, int deadline, bool periodic)
    {
      mID = id;
      mExecTime = execTime;
      mExecAlready = 0;
      mPeriodic = periodic;
      if (periodic)
      {
        mRelease = 0;
        mDeadline = deadline;
      }
      else
      { //aperiodic
        mRelease = deadline;
        mDeadline = deadline + 500; // implicit 500ms deadline
      }
    }
  private:
    char mID;
    int mExecTime;
    int mExecAlready;
    int mReleaseTime;
    int mDeadline;
    bool mPeriodic;
};
