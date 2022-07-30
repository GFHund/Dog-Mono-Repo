
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

#include <Entity/SessionHistoryPackageEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        SessionHistoryPackageEntity::SessionHistoryPackageEntity(){}
SessionHistoryPackageEntity::SessionHistoryPackageEntity(char* rawData,int size,int offset){
this->setHeader(HeaderEntity(rawData,size,offset+0));
this->setCarIdx(*((uint8_t*)(rawData+24)));
this->setNumLaps(*((uint8_t*)(rawData+25)));
this->setNumTyreStints(*((uint8_t*)(rawData+26)));
this->setBestLapTimeLapNum(*((uint8_t*)(rawData+27)));
this->setBestSector1LapNum(*((uint8_t*)(rawData+28)));
this->setBestSector2LapNum(*((uint8_t*)(rawData+29)));
this->setBestSector3LapNum(*((uint8_t*)(rawData+30)));
for(int i=0;i<100;i++){this->setLapHistoryData(i,LapHistoryDataEntity(rawData,size,offset+31+i*11));}
for(int i=0;i<8;i++){this->setTyreStintsHistoryData(i,TyreStintHistoryDataEntity(rawData,size,offset+1131+i*3));}
}

        HeaderEntity SessionHistoryPackageEntity::getHeader(){return this->header;}
uint8_t SessionHistoryPackageEntity::getCarIdx(){return this->carIdx;}
uint8_t SessionHistoryPackageEntity::getNumLaps(){return this->numLaps;}
uint8_t SessionHistoryPackageEntity::getNumTyreStints(){return this->numTyreStints;}
uint8_t SessionHistoryPackageEntity::getBestLapTimeLapNum(){return this->bestLapTimeLapNum;}
uint8_t SessionHistoryPackageEntity::getBestSector1LapNum(){return this->bestSector1LapNum;}
uint8_t SessionHistoryPackageEntity::getBestSector2LapNum(){return this->bestSector2LapNum;}
uint8_t SessionHistoryPackageEntity::getBestSector3LapNum(){return this->bestSector3LapNum;}
LapHistoryDataEntity* SessionHistoryPackageEntity::getLapHistoryData(){return this->lapHistoryData;}
TyreStintHistoryDataEntity* SessionHistoryPackageEntity::getTyreStintsHistoryData(){return this->tyreStintsHistoryData;}

        void SessionHistoryPackageEntity::setHeader(HeaderEntity header){this->header = header;}
void SessionHistoryPackageEntity::setCarIdx(uint8_t carIdx){this->carIdx = carIdx;}
void SessionHistoryPackageEntity::setNumLaps(uint8_t numLaps){this->numLaps = numLaps;}
void SessionHistoryPackageEntity::setNumTyreStints(uint8_t numTyreStints){this->numTyreStints = numTyreStints;}
void SessionHistoryPackageEntity::setBestLapTimeLapNum(uint8_t bestLapTimeLapNum){this->bestLapTimeLapNum = bestLapTimeLapNum;}
void SessionHistoryPackageEntity::setBestSector1LapNum(uint8_t bestSector1LapNum){this->bestSector1LapNum = bestSector1LapNum;}
void SessionHistoryPackageEntity::setBestSector2LapNum(uint8_t bestSector2LapNum){this->bestSector2LapNum = bestSector2LapNum;}
void SessionHistoryPackageEntity::setBestSector3LapNum(uint8_t bestSector3LapNum){this->bestSector3LapNum = bestSector3LapNum;}
void SessionHistoryPackageEntity::setLapHistoryData(int i,LapHistoryDataEntity lapHistoryData){this->lapHistoryData[i] = lapHistoryData;}
void SessionHistoryPackageEntity::setTyreStintsHistoryData(int i,TyreStintHistoryDataEntity tyreStintsHistoryData){this->tyreStintsHistoryData[i] = tyreStintsHistoryData;}


        std::string SessionHistoryPackageEntity::getTableName(){
            return "SessionHistoryPackageEntity";
        }
        std::string SessionHistoryPackageEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS SessionHistoryPackageEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`header` REAL,`carIdx` INTEGER,`numLaps` INTEGER,`numTyreStints` INTEGER,`bestLapTimeLapNum` INTEGER,`bestSector1LapNum` INTEGER,`bestSector2LapNum` INTEGER,`bestSector3LapNum` INTEGER,`lapHistoryData` INTEGER,`tyreStintsHistoryData` INTEGER)";
        }
        
        void SessionHistoryPackageEntity::matchIntData(std::string column,int data){
            DogGE::Database::AbstractEntity::matchIntData(column,data);

        }
        void SessionHistoryPackageEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void SessionHistoryPackageEntity::matchRealData(std::string column,float data){
            
        }
        void SessionHistoryPackageEntity::matchStringData(std::string column,std::string data){}
        void SessionHistoryPackageEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> SessionHistoryPackageEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            
            return ret;
        }
        std::map<std::string,int64_t> SessionHistoryPackageEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> SessionHistoryPackageEntity::getRealMap(){
            std::map<std::string,float> ret;
            
            return ret;
        }
        std::map<std::string,std::string> SessionHistoryPackageEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> SessionHistoryPackageEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        