
/**
 * @file F1DataClassTemplate.cpp
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

#include <Entity/LapDataPackageEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        LapDataPackageEntity::LapDataPackageEntity(){}
LapDataPackageEntity::LapDataPackageEntity(char* rawData,int size,int offset){
this->setHeader(HeaderEntity(rawData,size,offset+0));
for(int i=0;i<22;i++){this->setLapData(i,LapDataEntity(rawData,size,offset+24+i*43));}
this->setTimeTrialPBCarIdx(*((uint8_t*)(rawData+970)));
this->setTimeTrialRivalCarIdx(*((uint8_t*)(rawData+971)));
}

        HeaderEntity LapDataPackageEntity::getHeader(){return this->header;}
LapDataEntity* LapDataPackageEntity::getLapData(){return this->lapData;}
uint8_t LapDataPackageEntity::getTimeTrialPBCarIdx(){return this->timeTrialPBCarIdx;}
uint8_t LapDataPackageEntity::getTimeTrialRivalCarIdx(){return this->timeTrialRivalCarIdx;}

        void LapDataPackageEntity::setHeader(HeaderEntity header){this->header = header;}
void LapDataPackageEntity::setLapData(int i,LapDataEntity lapData){this->lapData[i] = lapData;}
void LapDataPackageEntity::setTimeTrialPBCarIdx(uint8_t timeTrialPBCarIdx){this->timeTrialPBCarIdx = timeTrialPBCarIdx;}
void LapDataPackageEntity::setTimeTrialRivalCarIdx(uint8_t timeTrialRivalCarIdx){this->timeTrialRivalCarIdx = timeTrialRivalCarIdx;}


        std::string LapDataPackageEntity::getTableName(){
            return "LapDataPackageEntity";
        }
        std::string LapDataPackageEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS LapDataPackageEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`header` REAL,`lapData` INTEGER,`timeTrialPBCarIdx` INTEGER,`timeTrialRivalCarIdx` INTEGER)";
        }
        
        void LapDataPackageEntity::matchIntData(std::string column,int data){
            DogGE::Database::AbstractEntity::matchIntData(column,data);

        }
        void LapDataPackageEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void LapDataPackageEntity::matchRealData(std::string column,float data){
            
        }
        void LapDataPackageEntity::matchStringData(std::string column,std::string data){}
        void LapDataPackageEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> LapDataPackageEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            
            return ret;
        }
        std::map<std::string,int64_t> LapDataPackageEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> LapDataPackageEntity::getRealMap(){
            std::map<std::string,float> ret;
            
            return ret;
        }
        std::map<std::string,std::string> LapDataPackageEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> LapDataPackageEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        