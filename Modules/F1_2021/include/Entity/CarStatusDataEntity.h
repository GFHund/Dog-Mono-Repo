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
        class CarStatusDataEntity: public DogGE::Database::AbstractEntity{
            private:
            uint8_t tractionControl;
uint8_t antiLockBrakes;
uint8_t fuelMix;
uint8_t frontBrakeBias;
uint8_t pitLimiterStatus;
float fuelInTank;
float fuelCapacity;
float fuelRemainingLaps;
uint16_t maxRPM;
uint16_t idleRPM;
uint8_t maxGears;
uint8_t drsAllowed;
uint16_t drsActivationDistance;
uint8_t actualTyreCompound;
uint8_t visualTyreCompound;
uint8_t tyresAgeLaps;
int8_t vehicleFiaFlags;
float ersStoreEnergy;
uint8_t ersDeployMode;
float ersHarvestedThisLapMGUK;
float ersHarvestedThisLapMGUH;
float ersDeployedThisLap;
uint8_t networkPaused;

            public:
            

            void setTractionControl(uint8_t tractionControl);
void setAntiLockBrakes(uint8_t antiLockBrakes);
void setFuelMix(uint8_t fuelMix);
void setFrontBrakeBias(uint8_t frontBrakeBias);
void setPitLimiterStatus(uint8_t pitLimiterStatus);
void setFuelInTank(float fuelInTank);
void setFuelCapacity(float fuelCapacity);
void setFuelRemainingLaps(float fuelRemainingLaps);
void setMaxRPM(uint16_t maxRPM);
void setIdleRPM(uint16_t idleRPM);
void setMaxGears(uint8_t maxGears);
void setDrsAllowed(uint8_t drsAllowed);
void setDrsActivationDistance(uint16_t drsActivationDistance);
void setActualTyreCompound(uint8_t actualTyreCompound);
void setVisualTyreCompound(uint8_t visualTyreCompound);
void setTyresAgeLaps(uint8_t tyresAgeLaps);
void setVehicleFiaFlags(int8_t vehicleFiaFlags);
void setErsStoreEnergy(float ersStoreEnergy);
void setErsDeployMode(uint8_t ersDeployMode);
void setErsHarvestedThisLapMGUK(float ersHarvestedThisLapMGUK);
void setErsHarvestedThisLapMGUH(float ersHarvestedThisLapMGUH);
void setErsDeployedThisLap(float ersDeployedThisLap);
void setNetworkPaused(uint8_t networkPaused);

            uint8_t getTractionControl();
uint8_t getAntiLockBrakes();
uint8_t getFuelMix();
uint8_t getFrontBrakeBias();
uint8_t getPitLimiterStatus();
float getFuelInTank();
float getFuelCapacity();
float getFuelRemainingLaps();
uint16_t getMaxRPM();
uint16_t getIdleRPM();
uint8_t getMaxGears();
uint8_t getDrsAllowed();
uint16_t getDrsActivationDistance();
uint8_t getActualTyreCompound();
uint8_t getVisualTyreCompound();
uint8_t getTyresAgeLaps();
int8_t getVehicleFiaFlags();
float getErsStoreEnergy();
uint8_t getErsDeployMode();
float getErsHarvestedThisLapMGUK();
float getErsHarvestedThisLapMGUH();
float getErsDeployedThisLap();
uint8_t getNetworkPaused();


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