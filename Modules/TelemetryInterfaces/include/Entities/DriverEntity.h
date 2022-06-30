#ifndef __DRIVER_ENTITY__
#define __DRIVER_ENTITY__
#pragma once

#include <AbstractEntity.h>

namespace CTelemetry{
    namespace Entity{
        class DriverEntity:public DogGE::Database::AbstractEntity{
            private:
            std::string driverName;
            int driverNumber;
            public:
            virtual std::string getTableName();
            virtual std::string getTableDefinition();
            
            virtual void matchIntData(std::string column,int data);
            virtual void matchRealData(std::string column,float data);
            virtual void matchStringData(std::string column,std::string data);
            virtual void matchRawData(std::string column,char* data,int length);

            virtual std::map<std::string,int> getIntMap();
            virtual std::map<std::string,float> getRealMap();
            virtual std::map<std::string,std::string> getStringMap();
            virtual std::map<std::string,std::pair<char*,int>> getRawMap();
        };
    }
}


#endif 