#include "TaskInterface.h"

TaskInterface::TaskInterface(){
    this->mPercentProcess = 0;
    this->mFinish = false;
}

bool TaskInterface::isFinish(){
    return this->mFinish;
}
void TaskInterface::process(){
    this->task();
}
unsigned char TaskInterface::getPercentProcess(){
    return this->mPercentProcess;
}
std::string TaskInterface::getError(){
    return this->mError;
}
TaskInterface::FINISH_MODE TaskInterface::getFinishMode(){
    return this->mFinishMode;
}