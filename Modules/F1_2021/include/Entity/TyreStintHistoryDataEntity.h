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

#ifndef ____F1_DATA_ENTITY____
#define ____F1_DATA_ENTITY____
#pragma once

#include <stdint.h>
#include <AbstractEntity.h>



namespace DogGE{
    namespace F1_2021{
        class TyreStintHistoryDataEntity: public DogGE::Database::AbstractEntity{
            private:
            uint8_t endLap;
uint8_t tyreActualCompound;
uint8_t tyreVisualCompound;

            public:
            

            void setEndLap(uint8_t endLap);
void setTyreActualCompound(uint8_t tyreActualCompound);
void setTyreVisualCompound(uint8_t tyreVisualCompound);

            uint8_t getEndLap();
uint8_t getTyreActualCompound();
uint8_t getTyreVisualCompound();


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