
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

#include <Entity/CarTelemetryDataEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        CarTelemetryDataEntity::CarTelemetryDataEntity(){}
CarTelemetryDataEntity::CarTelemetryDataEntity(char* rawData,int size,int offset){
this->setSpeed(*((uint16_t*)(rawData+0)));
this->setThrottle(*((float*)(rawData+2)));
this->setSteer(*((float*)(rawData+6)));
this->setBrake(*((float*)(rawData+10)));
this->setClutch(*((uint8_t*)(rawData+14)));
this->setGear(*((int8_t*)(rawData+15)));
this->setEngineRPM(*((uint16_t*)(rawData+16)));
this->setDrs(*((uint8_t*)(rawData+18)));
this->setRevLightsPercent(*((uint8_t*)(rawData+19)));
this->setRevLightsBitValue(*((uint16_t*)(rawData+20)));
this->setBrakesTemperatureRL(*((uint16_t*)(rawData+22)));
this->setBrakesTemperatureRR(*((uint16_t*)(rawData+24)));
this->setBrakesTemperatureFL(*((uint16_t*)(rawData+26)));
this->setBrakesTemperatureFR(*((uint16_t*)(rawData+28)));
this->setTyreSurfaceTemperatureRL(*((uint8_t*)(rawData+30)));
this->setTyreSurfaceTemperatureRR(*((uint8_t*)(rawData+31)));
this->setTyreSurfaceTemperatureFL(*((uint8_t*)(rawData+32)));
this->setTyreSurfaceTemperatureFR(*((uint8_t*)(rawData+33)));
this->setTyreInnerTemperatureRL(*((uint8_t*)(rawData+34)));
this->setTyreInnerTemperatureRR(*((uint8_t*)(rawData+35)));
this->setTyreInnerTemperatureFL(*((uint8_t*)(rawData+36)));
this->setTyreInnerTemperatureFR(*((uint8_t*)(rawData+37)));
this->setEngineTemperature(*((uint16_t*)(rawData+38)));
this->setTyresPressureRL(*((float*)(rawData+40)));
this->setTyresPressureRR(*((float*)(rawData+44)));
this->setTyresPressureFL(*((float*)(rawData+48)));
this->setTyresPressureFR(*((float*)(rawData+52)));
this->setSurfaceTypeRL(*((uint8_t*)(rawData+56)));
this->setSurfaceTypeRR(*((uint8_t*)(rawData+57)));
this->setSurfaceTypeFL(*((uint8_t*)(rawData+58)));
this->setSurfaceTypeFR(*((uint8_t*)(rawData+59)));
}

        uint16_t CarTelemetryDataEntity::getSpeed(){return this->speed;}
float CarTelemetryDataEntity::getThrottle(){return this->throttle;}
float CarTelemetryDataEntity::getSteer(){return this->steer;}
float CarTelemetryDataEntity::getBrake(){return this->brake;}
uint8_t CarTelemetryDataEntity::getClutch(){return this->clutch;}
int8_t CarTelemetryDataEntity::getGear(){return this->gear;}
uint16_t CarTelemetryDataEntity::getEngineRPM(){return this->engineRPM;}
uint8_t CarTelemetryDataEntity::getDrs(){return this->drs;}
uint8_t CarTelemetryDataEntity::getRevLightsPercent(){return this->revLightsPercent;}
uint16_t CarTelemetryDataEntity::getRevLightsBitValue(){return this->revLightsBitValue;}
uint16_t CarTelemetryDataEntity::getBrakesTemperatureRL(){return this->brakesTemperatureRL;}
uint16_t CarTelemetryDataEntity::getBrakesTemperatureRR(){return this->brakesTemperatureRR;}
uint16_t CarTelemetryDataEntity::getBrakesTemperatureFL(){return this->brakesTemperatureFL;}
uint16_t CarTelemetryDataEntity::getBrakesTemperatureFR(){return this->brakesTemperatureFR;}
uint8_t CarTelemetryDataEntity::getTyreSurfaceTemperatureRL(){return this->tyreSurfaceTemperatureRL;}
uint8_t CarTelemetryDataEntity::getTyreSurfaceTemperatureRR(){return this->tyreSurfaceTemperatureRR;}
uint8_t CarTelemetryDataEntity::getTyreSurfaceTemperatureFL(){return this->tyreSurfaceTemperatureFL;}
uint8_t CarTelemetryDataEntity::getTyreSurfaceTemperatureFR(){return this->tyreSurfaceTemperatureFR;}
uint8_t CarTelemetryDataEntity::getTyreInnerTemperatureRL(){return this->tyreInnerTemperatureRL;}
uint8_t CarTelemetryDataEntity::getTyreInnerTemperatureRR(){return this->tyreInnerTemperatureRR;}
uint8_t CarTelemetryDataEntity::getTyreInnerTemperatureFL(){return this->tyreInnerTemperatureFL;}
uint8_t CarTelemetryDataEntity::getTyreInnerTemperatureFR(){return this->tyreInnerTemperatureFR;}
uint16_t CarTelemetryDataEntity::getEngineTemperature(){return this->engineTemperature;}
float CarTelemetryDataEntity::getTyresPressureRL(){return this->tyresPressureRL;}
float CarTelemetryDataEntity::getTyresPressureRR(){return this->tyresPressureRR;}
float CarTelemetryDataEntity::getTyresPressureFL(){return this->tyresPressureFL;}
float CarTelemetryDataEntity::getTyresPressureFR(){return this->tyresPressureFR;}
uint8_t CarTelemetryDataEntity::getSurfaceTypeRL(){return this->surfaceTypeRL;}
uint8_t CarTelemetryDataEntity::getSurfaceTypeRR(){return this->surfaceTypeRR;}
uint8_t CarTelemetryDataEntity::getSurfaceTypeFL(){return this->surfaceTypeFL;}
uint8_t CarTelemetryDataEntity::getSurfaceTypeFR(){return this->surfaceTypeFR;}

        void CarTelemetryDataEntity::setSpeed(uint16_t speed){this->speed = speed;}
void CarTelemetryDataEntity::setThrottle(float throttle){this->throttle = throttle;}
void CarTelemetryDataEntity::setSteer(float steer){this->steer = steer;}
void CarTelemetryDataEntity::setBrake(float brake){this->brake = brake;}
void CarTelemetryDataEntity::setClutch(uint8_t clutch){this->clutch = clutch;}
void CarTelemetryDataEntity::setGear(int8_t gear){this->gear = gear;}
void CarTelemetryDataEntity::setEngineRPM(uint16_t engineRPM){this->engineRPM = engineRPM;}
void CarTelemetryDataEntity::setDrs(uint8_t drs){this->drs = drs;}
void CarTelemetryDataEntity::setRevLightsPercent(uint8_t revLightsPercent){this->revLightsPercent = revLightsPercent;}
void CarTelemetryDataEntity::setRevLightsBitValue(uint16_t revLightsBitValue){this->revLightsBitValue = revLightsBitValue;}
void CarTelemetryDataEntity::setBrakesTemperatureRL(uint16_t brakesTemperatureRL){this->brakesTemperatureRL = brakesTemperatureRL;}
void CarTelemetryDataEntity::setBrakesTemperatureRR(uint16_t brakesTemperatureRR){this->brakesTemperatureRR = brakesTemperatureRR;}
void CarTelemetryDataEntity::setBrakesTemperatureFL(uint16_t brakesTemperatureFL){this->brakesTemperatureFL = brakesTemperatureFL;}
void CarTelemetryDataEntity::setBrakesTemperatureFR(uint16_t brakesTemperatureFR){this->brakesTemperatureFR = brakesTemperatureFR;}
void CarTelemetryDataEntity::setTyreSurfaceTemperatureRL(uint8_t tyreSurfaceTemperatureRL){this->tyreSurfaceTemperatureRL = tyreSurfaceTemperatureRL;}
void CarTelemetryDataEntity::setTyreSurfaceTemperatureRR(uint8_t tyreSurfaceTemperatureRR){this->tyreSurfaceTemperatureRR = tyreSurfaceTemperatureRR;}
void CarTelemetryDataEntity::setTyreSurfaceTemperatureFL(uint8_t tyreSurfaceTemperatureFL){this->tyreSurfaceTemperatureFL = tyreSurfaceTemperatureFL;}
void CarTelemetryDataEntity::setTyreSurfaceTemperatureFR(uint8_t tyreSurfaceTemperatureFR){this->tyreSurfaceTemperatureFR = tyreSurfaceTemperatureFR;}
void CarTelemetryDataEntity::setTyreInnerTemperatureRL(uint8_t tyreInnerTemperatureRL){this->tyreInnerTemperatureRL = tyreInnerTemperatureRL;}
void CarTelemetryDataEntity::setTyreInnerTemperatureRR(uint8_t tyreInnerTemperatureRR){this->tyreInnerTemperatureRR = tyreInnerTemperatureRR;}
void CarTelemetryDataEntity::setTyreInnerTemperatureFL(uint8_t tyreInnerTemperatureFL){this->tyreInnerTemperatureFL = tyreInnerTemperatureFL;}
void CarTelemetryDataEntity::setTyreInnerTemperatureFR(uint8_t tyreInnerTemperatureFR){this->tyreInnerTemperatureFR = tyreInnerTemperatureFR;}
void CarTelemetryDataEntity::setEngineTemperature(uint16_t engineTemperature){this->engineTemperature = engineTemperature;}
void CarTelemetryDataEntity::setTyresPressureRL(float tyresPressureRL){this->tyresPressureRL = tyresPressureRL;}
void CarTelemetryDataEntity::setTyresPressureRR(float tyresPressureRR){this->tyresPressureRR = tyresPressureRR;}
void CarTelemetryDataEntity::setTyresPressureFL(float tyresPressureFL){this->tyresPressureFL = tyresPressureFL;}
void CarTelemetryDataEntity::setTyresPressureFR(float tyresPressureFR){this->tyresPressureFR = tyresPressureFR;}
void CarTelemetryDataEntity::setSurfaceTypeRL(uint8_t surfaceTypeRL){this->surfaceTypeRL = surfaceTypeRL;}
void CarTelemetryDataEntity::setSurfaceTypeRR(uint8_t surfaceTypeRR){this->surfaceTypeRR = surfaceTypeRR;}
void CarTelemetryDataEntity::setSurfaceTypeFL(uint8_t surfaceTypeFL){this->surfaceTypeFL = surfaceTypeFL;}
void CarTelemetryDataEntity::setSurfaceTypeFR(uint8_t surfaceTypeFR){this->surfaceTypeFR = surfaceTypeFR;}


        std::string CarTelemetryDataEntity::getTableName(){
            return "CarTelemetryDataEntity";
        }
        std::string CarTelemetryDataEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS CarTelemetryDataEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`speed` INTEGER,`throttle` REAL,`steer` REAL,`brake` REAL,`clutch` INTEGER,`gear` INTEGER,`engineRPM` INTEGER,`drs` INTEGER,`revLightsPercent` INTEGER,`revLightsBitValue` INTEGER,`brakesTemperatureRL` INTEGER,`brakesTemperatureRR` INTEGER,`brakesTemperatureFL` INTEGER,`brakesTemperatureFR` INTEGER,`tyreSurfaceTemperatureRL` INTEGER,`tyreSurfaceTemperatureRR` INTEGER,`tyreSurfaceTemperatureFL` INTEGER,`tyreSurfaceTemperatureFR` INTEGER,`tyreInnerTemperatureRL` INTEGER,`tyreInnerTemperatureRR` INTEGER,`tyreInnerTemperatureFL` INTEGER,`tyreInnerTemperatureFR` INTEGER,`engineTemperature` INTEGER,`tyresPressureRL` REAL,`tyresPressureRR` REAL,`tyresPressureFL` REAL,`tyresPressureFR` REAL,`surfaceTypeRL` INTEGER,`surfaceTypeRR` INTEGER,`surfaceTypeFL` INTEGER,`surfaceTypeFR` INTEGER)";
        }
        
        void CarTelemetryDataEntity::matchIntData(std::string column,int data){
            if(column.compare("gear") == 0){
this->setGear(data);
} else {DogGE::Database::AbstractEntity::matchIntData(column,data);}

        }
        void CarTelemetryDataEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void CarTelemetryDataEntity::matchRealData(std::string column,float data){
            if(column.compare("throttle") == 0){
this->setThrottle(data);
} else if(column.compare("steer") == 0){
this->setSteer(data);
} else if(column.compare("brake") == 0){
this->setBrake(data);
} else if(column.compare("tyresPressureRL") == 0){
this->setTyresPressureRL(data);
} else if(column.compare("tyresPressureRR") == 0){
this->setTyresPressureRR(data);
} else if(column.compare("tyresPressureFL") == 0){
this->setTyresPressureFL(data);
} else if(column.compare("tyresPressureFR") == 0){
this->setTyresPressureFR(data);
}
        }
        void CarTelemetryDataEntity::matchStringData(std::string column,std::string data){}
        void CarTelemetryDataEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> CarTelemetryDataEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            ret.insert(std::pair<std::string,int>("gear",this->getGear()));

            return ret;
        }
        std::map<std::string,int64_t> CarTelemetryDataEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> CarTelemetryDataEntity::getRealMap(){
            std::map<std::string,float> ret;
            ret.insert(std::pair<std::string,float>("throttle",this->getThrottle()));ret.insert(std::pair<std::string,float>("steer",this->getSteer()));ret.insert(std::pair<std::string,float>("brake",this->getBrake()));ret.insert(std::pair<std::string,float>("tyresPressureRL",this->getTyresPressureRL()));ret.insert(std::pair<std::string,float>("tyresPressureRR",this->getTyresPressureRR()));ret.insert(std::pair<std::string,float>("tyresPressureFL",this->getTyresPressureFL()));ret.insert(std::pair<std::string,float>("tyresPressureFR",this->getTyresPressureFR()));
            return ret;
        }
        std::map<std::string,std::string> CarTelemetryDataEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> CarTelemetryDataEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        