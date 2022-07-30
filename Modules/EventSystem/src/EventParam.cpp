#include "EventParam.h"
#include <utility>
#include <exception>
#include <stdexcept>

EventParam::~EventParam(){
    for(std::map<std::string,ParamValue>::iterator it = mParams.begin();
    it!=mParams.end();++it){
        delete[] it->second.value;
    }
}
void EventParam::insertIntoMap(std::string name,char* value,int bytes){
    ParamValue obj;
    obj.num = bytes;
    obj.value = value;

    std::pair<std::string, ParamValue> insert;
    insert = std::make_pair(name, obj);
    mParams.insert( insert );
}
void EventParam::setInt( std::string name,int value){
    int bytes = sizeof(value);
    char* byteArray = (char *)&value;
    char* byteArray2 = new char[bytes];
    for(int i=0;i<bytes;i++){
        byteArray2[i] = byteArray[i];
    }
    insertIntoMap(name,byteArray2,bytes);
}
void EventParam::setFloat(std::string name,float value){
    int bytes = sizeof(value);
    char* floatArray = (char*)&value;
    char* copyArray = new char[bytes];
    for(int i=0;i<bytes;i++){
        copyArray[i] = floatArray[i];
    }
    insertIntoMap(name,copyArray,bytes);
}
void EventParam::setString(std::string name,std::string value){
    int bytes = value.length();
    const char* floatArray = value.c_str();
    char* copyArray = new char[bytes];
    for(int i=0;i<bytes;i++){
        copyArray[i] = floatArray[i];
    }
    insertIntoMap(name,copyArray,bytes);
}
void EventParam::setDouble(std::string name,double value){
  int bytes = sizeof(value);
  char* doubleArray = (char*)&value;
  char* copyArray = new char[bytes];
  for(int i=0;i<bytes;i++){
    copyArray[i] = doubleArray[i];
  }
  insertIntoMap(name,copyArray,bytes);
}
void EventParam::setChar(std::string name,char value){
  int bytes = sizeof(value);
  char* copy = new char;
  *copy = value;
  insertIntoMap(name,copy,bytes);
}

int EventParam::getInt(std::string name){
    try{
      ParamValue val = mParams.at(name);
      if(val.num != sizeof(int)){
        throw std::exception();
      }
      int* value = (int*)val.value;
      return *value;
    }catch(std::out_of_range e){
      throw e;
    }
}
float EventParam::getFloat(std::string name){
  try{
    ParamValue val = mParams.at(name);
    if(val.num != sizeof(float)){
        throw std::exception();
    }
    float* value = (float*)val.value;
    return *value;
    
  }catch(std::out_of_range e){
    throw e;
  }
}
std::string EventParam::getString(std::string name){
  try{
    ParamValue val = mParams.at(name);
    std::string str = std::string();
    for(int i=0;i<val.num;i++){
        str += val.value[i];
    }
    return str;
    
  }catch(std::out_of_range e){
    throw e;
  }
}
double EventParam::getDouble(std::string name){
  try{
    ParamValue val = mParams.at(name);
    if(val.num != sizeof(double)){
      throw std::exception();
    }
    double* value = (double*)val.value;
    return *value;
  }
  catch(std::out_of_range e){
    throw e;
  }
  
}
char EventParam::getChar(std::string name){
  try{
    ParamValue val = mParams.at(name);
    if(val.num != sizeof(char)){
      throw std::exception();
    }
    return *(val.value);
  }catch(std::out_of_range e){
    throw e;
  }
  
}