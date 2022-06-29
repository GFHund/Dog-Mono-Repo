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

#ifndef __CAR_SETUP_DATA__
#define __CAR_SETUP_DATA__
#pragma once

#include <stdint.h>


namespace DogGE{
    namespace F1_2022{
        class CarSetupData{
            private:
            uint8_t frontWing;
uint8_t rearWing;
uint8_t onThrottle;
uint8_t offThrottle;
float frontCamber;
float rearCamber;
float frontToe;
float rearToe;
uint8_t frontSuspension;
uint8_t rearSuspension;
uint8_t frontAntiRollBar;
uint8_t rearAntiRollBar;
uint8_t frontSuspensionHeight;
uint8_t rearSuspensionHeight;
uint8_t breakePressure;
uint8_t breakeBias;
float rearLeftTyrePressure;
float rearRightTyrePressure;
float frontLeftTyrePressure;
float frontRightTyrePressure;
uint8_t ballast;
float fuelLoad;

            public:
            void setFrontWing(uint8_t frontWing);
void setRearWing(uint8_t rearWing);
void setOnThrottle(uint8_t onThrottle);
void setOffThrottle(uint8_t offThrottle);
void setFrontCamber(float frontCamber);
void setRearCamber(float rearCamber);
void setFrontToe(float frontToe);
void setRearToe(float rearToe);
void setFrontSuspension(uint8_t frontSuspension);
void setRearSuspension(uint8_t rearSuspension);
void setFrontAntiRollBar(uint8_t frontAntiRollBar);
void setRearAntiRollBar(uint8_t rearAntiRollBar);
void setFrontSuspensionHeight(uint8_t frontSuspensionHeight);
void setRearSuspensionHeight(uint8_t rearSuspensionHeight);
void setBreakePressure(uint8_t breakePressure);
void setBreakeBias(uint8_t breakeBias);
void setRearLeftTyrePressure(float rearLeftTyrePressure);
void setRearRightTyrePressure(float rearRightTyrePressure);
void setFrontLeftTyrePressure(float frontLeftTyrePressure);
void setFrontRightTyrePressure(float frontRightTyrePressure);
void setBallast(uint8_t ballast);
void setFuelLoad(float fuelLoad);

            uint8_t getFrontWing();
uint8_t getRearWing();
uint8_t getOnThrottle();
uint8_t getOffThrottle();
float getFrontCamber();
float getRearCamber();
float getFrontToe();
float getRearToe();
uint8_t getFrontSuspension();
uint8_t getRearSuspension();
uint8_t getFrontAntiRollBar();
uint8_t getRearAntiRollBar();
uint8_t getFrontSuspensionHeight();
uint8_t getRearSuspensionHeight();
uint8_t getBreakePressure();
uint8_t getBreakeBias();
float getRearLeftTyrePressure();
float getRearRightTyrePressure();
float getFrontLeftTyrePressure();
float getFrontRightTyrePressure();
uint8_t getBallast();
float getFuelLoad();

        };
    }
}

#endif                                