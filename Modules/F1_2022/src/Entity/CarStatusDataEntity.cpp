
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

#include <Entity/CarStatusDataEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        CarStatusDataEntity::CarStatusDataEntity(){}
CarStatusDataEntity::CarStatusDataEntity(char* rawData,int size,int offset){
this->setTractionControl(*((uint8_t*)(rawData+0)));
this->setAntiLockBrakes(*((uint8_t*)(rawData+1)));
this->setFuelMix(*((uint8_t*)(rawData+2)));
this->setFrontBrakeBias(*((uint8_t*)(rawData+3)));
this->setPitLimiterStatus(*((uint8_t*)(rawData+4)));
this->setFuelInTank(*((float*)(rawData+5)));
this->setFuelCapacity(*((float*)(rawData+9)));
this->setFuelRemainingLaps(*((float*)(rawData+13)));
this->setMaxRPM(*((uint16_t*)(rawData+17)));
this->setIdleRPM(*((uint16_t*)(rawData+19)));
this->setMaxGears(*((uint8_t*)(rawData+21)));
this->setDrsAllowed(*((uint8_t*)(rawData+22)));
this->setDrsActivationDistance(*((uint16_t*)(rawData+23)));
this->setActualTyreCompound(*((uint8_t*)(rawData+25)));
this->setVisualTyreCompound(*((uint8_t*)(rawData+26)));
this->setTyresAgeLaps(*((uint8_t*)(rawData+27)));
this->setVehicleFiaFlags(*((int8_t*)(rawData+28)));
this->setErsStoreEnergy(*((float*)(rawData+29)));
this->setErsDeployMode(*((uint8_t*)(rawData+33)));
this->setErsHarvestedThisLapMGUK(*((float*)(rawData+34)));
this->setErsHarvestedThisLapMGUH(*((float*)(rawData+38)));
this->setErsDeployedThisLap(*((float*)(rawData+42)));
this->setNetworkPaused(*((uint8_t*)(rawData+46)));
}

        uint8_t CarStatusDataEntity::getTractionControl(){return this->tractionControl;}
uint8_t CarStatusDataEntity::getAntiLockBrakes(){return this->antiLockBrakes;}
uint8_t CarStatusDataEntity::getFuelMix(){return this->fuelMix;}
uint8_t CarStatusDataEntity::getFrontBrakeBias(){return this->frontBrakeBias;}
uint8_t CarStatusDataEntity::getPitLimiterStatus(){return this->pitLimiterStatus;}
float CarStatusDataEntity::getFuelInTank(){return this->fuelInTank;}
float CarStatusDataEntity::getFuelCapacity(){return this->fuelCapacity;}
float CarStatusDataEntity::getFuelRemainingLaps(){return this->fuelRemainingLaps;}
uint16_t CarStatusDataEntity::getMaxRPM(){return this->maxRPM;}
uint16_t CarStatusDataEntity::getIdleRPM(){return this->idleRPM;}
uint8_t CarStatusDataEntity::getMaxGears(){return this->maxGears;}
uint8_t CarStatusDataEntity::getDrsAllowed(){return this->drsAllowed;}
uint16_t CarStatusDataEntity::getDrsActivationDistance(){return this->drsActivationDistance;}
uint8_t CarStatusDataEntity::getActualTyreCompound(){return this->actualTyreCompound;}
uint8_t CarStatusDataEntity::getVisualTyreCompound(){return this->visualTyreCompound;}
uint8_t CarStatusDataEntity::getTyresAgeLaps(){return this->tyresAgeLaps;}
int8_t CarStatusDataEntity::getVehicleFiaFlags(){return this->vehicleFiaFlags;}
float CarStatusDataEntity::getErsStoreEnergy(){return this->ersStoreEnergy;}
uint8_t CarStatusDataEntity::getErsDeployMode(){return this->ersDeployMode;}
float CarStatusDataEntity::getErsHarvestedThisLapMGUK(){return this->ersHarvestedThisLapMGUK;}
float CarStatusDataEntity::getErsHarvestedThisLapMGUH(){return this->ersHarvestedThisLapMGUH;}
float CarStatusDataEntity::getErsDeployedThisLap(){return this->ersDeployedThisLap;}
uint8_t CarStatusDataEntity::getNetworkPaused(){return this->networkPaused;}

        void CarStatusDataEntity::setTractionControl(uint8_t tractionControl){this->tractionControl = tractionControl;}
void CarStatusDataEntity::setAntiLockBrakes(uint8_t antiLockBrakes){this->antiLockBrakes = antiLockBrakes;}
void CarStatusDataEntity::setFuelMix(uint8_t fuelMix){this->fuelMix = fuelMix;}
void CarStatusDataEntity::setFrontBrakeBias(uint8_t frontBrakeBias){this->frontBrakeBias = frontBrakeBias;}
void CarStatusDataEntity::setPitLimiterStatus(uint8_t pitLimiterStatus){this->pitLimiterStatus = pitLimiterStatus;}
void CarStatusDataEntity::setFuelInTank(float fuelInTank){this->fuelInTank = fuelInTank;}
void CarStatusDataEntity::setFuelCapacity(float fuelCapacity){this->fuelCapacity = fuelCapacity;}
void CarStatusDataEntity::setFuelRemainingLaps(float fuelRemainingLaps){this->fuelRemainingLaps = fuelRemainingLaps;}
void CarStatusDataEntity::setMaxRPM(uint16_t maxRPM){this->maxRPM = maxRPM;}
void CarStatusDataEntity::setIdleRPM(uint16_t idleRPM){this->idleRPM = idleRPM;}
void CarStatusDataEntity::setMaxGears(uint8_t maxGears){this->maxGears = maxGears;}
void CarStatusDataEntity::setDrsAllowed(uint8_t drsAllowed){this->drsAllowed = drsAllowed;}
void CarStatusDataEntity::setDrsActivationDistance(uint16_t drsActivationDistance){this->drsActivationDistance = drsActivationDistance;}
void CarStatusDataEntity::setActualTyreCompound(uint8_t actualTyreCompound){this->actualTyreCompound = actualTyreCompound;}
void CarStatusDataEntity::setVisualTyreCompound(uint8_t visualTyreCompound){this->visualTyreCompound = visualTyreCompound;}
void CarStatusDataEntity::setTyresAgeLaps(uint8_t tyresAgeLaps){this->tyresAgeLaps = tyresAgeLaps;}
void CarStatusDataEntity::setVehicleFiaFlags(int8_t vehicleFiaFlags){this->vehicleFiaFlags = vehicleFiaFlags;}
void CarStatusDataEntity::setErsStoreEnergy(float ersStoreEnergy){this->ersStoreEnergy = ersStoreEnergy;}
void CarStatusDataEntity::setErsDeployMode(uint8_t ersDeployMode){this->ersDeployMode = ersDeployMode;}
void CarStatusDataEntity::setErsHarvestedThisLapMGUK(float ersHarvestedThisLapMGUK){this->ersHarvestedThisLapMGUK = ersHarvestedThisLapMGUK;}
void CarStatusDataEntity::setErsHarvestedThisLapMGUH(float ersHarvestedThisLapMGUH){this->ersHarvestedThisLapMGUH = ersHarvestedThisLapMGUH;}
void CarStatusDataEntity::setErsDeployedThisLap(float ersDeployedThisLap){this->ersDeployedThisLap = ersDeployedThisLap;}
void CarStatusDataEntity::setNetworkPaused(uint8_t networkPaused){this->networkPaused = networkPaused;}


        std::string CarStatusDataEntity::getTableName(){
            return "CarStatusDataEntity";
        }
        std::string CarStatusDataEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS CarStatusDataEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`tractionControl` INTEGER,`antiLockBrakes` INTEGER,`fuelMix` INTEGER,`frontBrakeBias` INTEGER,`pitLimiterStatus` INTEGER,`fuelInTank` REAL,`fuelCapacity` REAL,`fuelRemainingLaps` REAL,`maxRPM` INTEGER,`idleRPM` INTEGER,`maxGears` INTEGER,`drsAllowed` INTEGER,`drsActivationDistance` INTEGER,`actualTyreCompound` INTEGER,`visualTyreCompound` INTEGER,`tyresAgeLaps` INTEGER,`vehicleFiaFlags` INTEGER,`ersStoreEnergy` REAL,`ersDeployMode` INTEGER,`ersHarvestedThisLapMGUK` REAL,`ersHarvestedThisLapMGUH` REAL,`ersDeployedThisLap` REAL,`networkPaused` INTEGER)";
        }
        
        void CarStatusDataEntity::matchIntData(std::string column,int data){
            if(column.compare("vehicleFiaFlags") == 0){
this->setVehicleFiaFlags(data);
} else {DogGE::Database::AbstractEntity::matchIntData(column,data);}

        }
        void CarStatusDataEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void CarStatusDataEntity::matchRealData(std::string column,float data){
            if(column.compare("fuelInTank") == 0){
this->setFuelInTank(data);
} else if(column.compare("fuelCapacity") == 0){
this->setFuelCapacity(data);
} else if(column.compare("fuelRemainingLaps") == 0){
this->setFuelRemainingLaps(data);
} else if(column.compare("ersStoreEnergy") == 0){
this->setErsStoreEnergy(data);
} else if(column.compare("ersHarvestedThisLapMGUK") == 0){
this->setErsHarvestedThisLapMGUK(data);
} else if(column.compare("ersHarvestedThisLapMGUH") == 0){
this->setErsHarvestedThisLapMGUH(data);
} else if(column.compare("ersDeployedThisLap") == 0){
this->setErsDeployedThisLap(data);
}
        }
        void CarStatusDataEntity::matchStringData(std::string column,std::string data){}
        void CarStatusDataEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> CarStatusDataEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            ret.insert(std::pair<std::string,int>("vehicleFiaFlags",this->getVehicleFiaFlags()));

            return ret;
        }
        std::map<std::string,int64_t> CarStatusDataEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> CarStatusDataEntity::getRealMap(){
            std::map<std::string,float> ret;
            ret.insert(std::pair<std::string,float>("fuelInTank",this->getFuelInTank()));ret.insert(std::pair<std::string,float>("fuelCapacity",this->getFuelCapacity()));ret.insert(std::pair<std::string,float>("fuelRemainingLaps",this->getFuelRemainingLaps()));ret.insert(std::pair<std::string,float>("ersStoreEnergy",this->getErsStoreEnergy()));ret.insert(std::pair<std::string,float>("ersHarvestedThisLapMGUK",this->getErsHarvestedThisLapMGUK()));ret.insert(std::pair<std::string,float>("ersHarvestedThisLapMGUH",this->getErsHarvestedThisLapMGUH()));ret.insert(std::pair<std::string,float>("ersDeployedThisLap",this->getErsDeployedThisLap()));
            return ret;
        }
        std::map<std::string,std::string> CarStatusDataEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> CarStatusDataEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        