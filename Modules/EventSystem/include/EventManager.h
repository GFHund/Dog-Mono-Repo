#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include "AbstractEvent.h"
#include "EventParam.h"
#include <string>
#include <map>
#include <vector>

class EventManager{
    private:
    EventManager();
    EventManager(EventManager& copy);
    static EventManager* instance;
    std::map<std::string,std::vector<AbstractEvent*>> mEvents;

    public:
    static EventManager* getInstance();
    void subscribe(std::string name,AbstractEvent* event);
    void fireEvent(std::string name,EventParam* param = nullptr);
};

#endif