#include "EventManager.h"
#include <stdexcept>
#include <iostream>

EventManager* EventManager::instance = nullptr;

EventManager::EventManager(){

}

EventManager* EventManager::getInstance(){
    if(instance == nullptr){
        instance = new EventManager();
    }
    return instance;
}

void EventManager::subscribe(std::string name,AbstractEvent* event){
    std::cout << "Subscribe " << name << std::endl;
    try{
      
        std::vector<AbstractEvent*>& vec = mEvents.at(name);
        vec.push_back(event);
        std::cout << "Insert into "<< name << std::endl;
    }catch(std::out_of_range e){
      std::cout << name << " not registered. creating new one" << std::endl;
        std::vector<AbstractEvent*> vec;
        vec.push_back(event);
        mEvents.insert(std::pair<std::string,std::vector<AbstractEvent*>>(name,vec));
    }
}
void EventManager::fireEvent(std::string name,EventParam* param){
    try{
        std::vector<AbstractEvent*> vec = mEvents.at(name);
        //std::cout << "Fire Event: "<< name << " " << vec.size() << std::endl;
        for(auto it = vec.begin();it != vec.end();++it){
            (*it)->event(name,param);
        }
        delete param;
    } catch(std::out_of_range e){
      delete param;
      //throw e;
    }
}