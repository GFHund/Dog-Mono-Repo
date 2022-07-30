#ifndef __TASK_MANAGER__
#define __TASK_MANAGER__

#include <vector>
#include <list>
#include <queue>
#include <mutex>
#include "TaskInterface.h"

class TaskManager{
    private:
    std::list<TaskInterface*> mFinishTasks;
    std::queue<TaskInterface*> mTaskQueue;
    std::mutex mMutex;
    
    bool mRunning;

    TaskManager();
    ~TaskManager();
    static TaskManager* mInstance;

    protected:
    void taskRunner();

    public:
    static TaskManager* getInstance();
    void addTask(TaskInterface* newTask);
    
};

#endif