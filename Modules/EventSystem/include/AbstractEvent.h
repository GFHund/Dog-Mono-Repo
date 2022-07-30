#ifndef __ABSTRACT_EVENT__
#define __ABSTRACT_EVENT__
#include <string>
#include "EventParam.h"
class AbstractEvent{
    public:
    virtual void event(std::string eventName,EventParam* param = nullptr) = 0;
};

#endif