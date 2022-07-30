#include "TaskManager.h"
#include <thread>
#include <iostream>

TaskManager* TaskManager::mInstance = 0;

TaskManager::TaskManager()
:mRunning(true){
    std::thread(&TaskManager::taskRunner,this).detach();
}
TaskManager::~TaskManager(){
    this->mRunning = false;
}

TaskManager* TaskManager::getInstance(){
    if(!mInstance){
        mInstance = new TaskManager();
    }
    return mInstance;
}

void TaskManager::taskRunner(){
    std::cout << "run TaskRunner" << std::endl;
    while(this->mRunning){
        if(this->mTaskQueue.size() <= 0){
            continue;
        }
        std::cout << this->mTaskQueue.size() << std::endl;
        this->mMutex.lock();
        TaskInterface* task = this->mTaskQueue.front();
        this->mTaskQueue.pop();
        this->mMutex.unlock();

        task->process();
        if(task->isFinish()){
            //std::cout << "Task Finished" << std::endl;
            //this->mFinishTasks.push_back(task);
            //std::cout << "Task Finished after" << std::endl;
        }
        else {
            this->mMutex.lock();
            this->mTaskQueue.push(task);
            this->mMutex.unlock();
        }
    }
    std::cout << "end Task Runner" << std::endl;
}

void TaskManager::addTask(TaskInterface* task){
    this->mMutex.lock();
    this->mTaskQueue.push(task);
    this->mMutex.unlock();
}