#ifndef __TASK_INTERFACE__
#define __TASK_INTERFACE__

#include <string>
class TaskInterface{
    public:
    enum FINISH_MODE{FINISH_WITH_SUCCESS,FINISH_WITH_ERROR};

    protected:
    bool mFinish;
    FINISH_MODE mFinishMode;
    unsigned char mPercentProcess;
    std::string mError;

    virtual void task() = 0;
    public:
    TaskInterface();
    bool isFinish();
    unsigned char getPercentProcess();
    void process();
    std::string getError();
    FINISH_MODE getFinishMode();
};

#endif