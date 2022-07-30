#ifndef __ABSTRACT_ENTITY__
#define __ABSTRACT_ENTITY__
#pragma once
#include <string>
#include <map>
//#include <Database.h>
#include <vector>

namespace DogGE{
    namespace Database{
        class AbstractEntity{
            protected:
            int id;
            public:
            AbstractEntity();

            virtual std::string getTableName() = 0;
            virtual std::string getTableDefinition() = 0;
            //virtual std::vector<std::string,Database::ColumnType> getColumns() = 0;
            
            virtual void matchIntData(std::string column,int data);
            virtual void matchInt64Data(std::string column,int64_t data);
            virtual void matchRealData(std::string column,float data);
            virtual void matchStringData(std::string column,std::string data);
            virtual void matchRawData(std::string column,char* data,int length);
            virtual void setEntityRelations(std::string column,AbstractEntity* entity);
            virtual void setEntityArrayRelations(std::string column,std::vector<AbstractEntity*> entities);
            

            virtual std::map<std::string,int> getIntMap();
            virtual std::map<std::string,int64_t> getInt64Map();
            virtual std::map<std::string,float> getRealMap();
            virtual std::map<std::string,std::string> getStringMap();
            virtual std::map<std::string,std::pair<char*,int>> getRawMap();
            virtual std::map<std::string,std::vector<AbstractEntity*>> get1ToNRelations();
            virtual std::map<std::string,AbstractEntity*> getNTo1Relations();

            virtual int getId();
            virtual void setId(int id);
        };
    }
}

#endif