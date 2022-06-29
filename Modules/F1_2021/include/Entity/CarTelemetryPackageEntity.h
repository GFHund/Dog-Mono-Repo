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
        class CarTelemetryPackageEntity: public DogGE::Database::AbstractEntity{
            private:
            Header header;
CarTelemetryData carTelemetry[22];
uint8_t mfdPanelIndex;
uint8_t mfdPanelIndexSecondaryPlayer;
int8_t suggestedGear;

            public:
            

            void setHeader(Header header);
void setCarTelemetry(CarTelemetryData* carTelemetry);
void setMfdPanelIndex(uint8_t mfdPanelIndex);
void setMfdPanelIndexSecondaryPlayer(uint8_t mfdPanelIndexSecondaryPlayer);
void setSuggestedGear(int8_t suggestedGear);

            Header getHeader();
CarTelemetryData* getCarTelemetry();
uint8_t getMfdPanelIndex();
uint8_t getMfdPanelIndexSecondaryPlayer();
int8_t getSuggestedGear();


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