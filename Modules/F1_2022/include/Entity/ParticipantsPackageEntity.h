/**
 * @file F1DataClassTemplate.h
 * @author Philipp Holzmann (Philipp1990@web.de)
 * @brief 
 * @version 1.0
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * This file ist generated by the f1GameParserGenerator Program. Any changes will be overriden.
 * 
 */

#ifndef ____ParticipantsPackage_ENTITY____
#define ____ParticipantsPackage_ENTITY____
#pragma once

#include <stdint.h>
#include <AbstractEntity.h>

#include <Entity/HeaderEntity.h>
#include <Entity/ParticipantsDataEntity.h>


namespace DogGE{
    namespace F1_2022{
        class ParticipantsPackageEntity: public DogGE::Database::AbstractEntity{
            private:
            HeaderEntity header;
uint8_t numActiveCars;
ParticipantsDataEntity participants[22];

            public:
            ParticipantsPackageEntity();
ParticipantsPackageEntity(char* rawData,int size,int offset=0);


            void setHeader(HeaderEntity header);
void setNumActiveCars(uint8_t numActiveCars);
void setParticipants(int i,ParticipantsDataEntity participants);

            HeaderEntity getHeader();
uint8_t getNumActiveCars();
ParticipantsDataEntity* getParticipants();


            virtual std::string getTableName();
            virtual std::string getTableDefinition();
            
            virtual void matchIntData(std::string column,int data);
            virtual void matchInt64Data(std::string column,int64_t data);
            virtual void matchRealData(std::string column,float data);
            virtual void matchStringData(std::string column,std::string data);
            virtual void matchRawData(std::string column,char* data,int length);

            virtual std::map<std::string,int> getIntMap();
            virtual std::map<std::string,int64_t> getInt64Map();
            virtual std::map<std::string,float> getRealMap();
            virtual std::map<std::string,std::string> getStringMap();
            virtual std::map<std::string,std::pair<char*,int>> getRawMap();
        };
    }
}

#endif                                                   