
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

#include <Entity/FinalClassificationPackageEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        FinalClassificationPackageEntity::FinalClassificationPackageEntity(){}
FinalClassificationPackageEntity::FinalClassificationPackageEntity(char* rawData,int size,int offset){
this->setHeader(HeaderEntity(rawData,size,offset+0));
this->setNumCars(*((uint8_t*)(rawData+24)));
for(int i=0;i<22;i++){this->setClassification(i,FinalClassificationDataEntity(rawData,size,offset+25+i*45));}
}

        HeaderEntity FinalClassificationPackageEntity::getHeader(){return this->header;}
uint8_t FinalClassificationPackageEntity::getNumCars(){return this->numCars;}
FinalClassificationDataEntity* FinalClassificationPackageEntity::getClassification(){return this->classification;}

        void FinalClassificationPackageEntity::setHeader(HeaderEntity header){this->header = header;}
void FinalClassificationPackageEntity::setNumCars(uint8_t numCars){this->numCars = numCars;}
void FinalClassificationPackageEntity::setClassification(int i,FinalClassificationDataEntity classification){this->classification[i] = classification;}


        std::string FinalClassificationPackageEntity::getTableName(){
            return "FinalClassificationPackageEntity";
        }
        std::string FinalClassificationPackageEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS FinalClassificationPackageEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`header` REAL,`numCars` INTEGER,`classification` INTEGER)";
        }
        
        void FinalClassificationPackageEntity::matchIntData(std::string column,int data){
            DogGE::Database::AbstractEntity::matchIntData(column,data);

        }
        void FinalClassificationPackageEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void FinalClassificationPackageEntity::matchRealData(std::string column,float data){
            
        }
        void FinalClassificationPackageEntity::matchStringData(std::string column,std::string data){}
        void FinalClassificationPackageEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> FinalClassificationPackageEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            
            return ret;
        }
        std::map<std::string,int64_t> FinalClassificationPackageEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> FinalClassificationPackageEntity::getRealMap(){
            std::map<std::string,float> ret;
            
            return ret;
        }
        std::map<std::string,std::string> FinalClassificationPackageEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> FinalClassificationPackageEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        