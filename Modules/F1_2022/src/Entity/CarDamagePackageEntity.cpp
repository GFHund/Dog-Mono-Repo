
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

#include <Entity/CarDamagePackageEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        CarDamagePackageEntity::CarDamagePackageEntity(){}
CarDamagePackageEntity::CarDamagePackageEntity(char* rawData,int size,int offset){
this->setHeader(HeaderEntity(rawData,size,offset+0));
for(int i=0;i<22;i++){this->setCarDamage(i,CarDamageDataEntity(rawData,size,offset+24+i*42));}
}

        HeaderEntity CarDamagePackageEntity::getHeader(){return this->header;}
CarDamageDataEntity* CarDamagePackageEntity::getCarDamage(){return this->carDamage;}

        void CarDamagePackageEntity::setHeader(HeaderEntity header){this->header = header;}
void CarDamagePackageEntity::setCarDamage(int i,CarDamageDataEntity carDamage){this->carDamage[i] = carDamage;}


        std::string CarDamagePackageEntity::getTableName(){
            return "CarDamagePackageEntity";
        }
        std::string CarDamagePackageEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS CarDamagePackageEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`header` REAL,`carDamage` INTEGER)";
        }
        
        void CarDamagePackageEntity::matchIntData(std::string column,int data){
            DogGE::Database::AbstractEntity::matchIntData(column,data);

        }
        void CarDamagePackageEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void CarDamagePackageEntity::matchRealData(std::string column,float data){
            
        }
        void CarDamagePackageEntity::matchStringData(std::string column,std::string data){}
        void CarDamagePackageEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> CarDamagePackageEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            
            return ret;
        }
        std::map<std::string,int64_t> CarDamagePackageEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> CarDamagePackageEntity::getRealMap(){
            std::map<std::string,float> ret;
            
            return ret;
        }
        std::map<std::string,std::string> CarDamagePackageEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> CarDamagePackageEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        