#ifndef __EVENT_PARAM__
#define __EVENT_PARAM__
#include <map>
#include <string>



class EventParam{
    private:
    struct ParamValue{
        int num;
        char* value;
    };
    std::map<std::string,ParamValue> mParams;

    void insertIntoMap(std::string name,char* value,int bytes);
    public:
    ~EventParam();
    void setInt(std::string name,int value);
    void setFloat(std::string name,float value);
    void setString(std::string name,std::string value);
    void setDouble(std::string name,double value);
    void setChar(std::string name,char value);
    int getInt(std::string name);
    float getFloat(std::string name);
    std::string getString(std::string name);
    double getDouble(std::string name);
    char getChar(std::string name);
};

#endif