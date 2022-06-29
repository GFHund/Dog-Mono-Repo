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

#include <DataClass/CarMotionData.h>

namespace DogGE{
    namespace F1_2021{
        float CarMotionData::getWorldPositionX(){return this->worldPositionX;}
float CarMotionData::getWorldPositionY(){return this->worldPositionY;}
float CarMotionData::getWorldPositionZ(){return this->worldPositionZ;}
float CarMotionData::getWorldVelocityX(){return this->worldVelocityX;}
float CarMotionData::getWorldVelocityY(){return this->worldVelocityY;}
float CarMotionData::getWorldVelocityZ(){return this->worldVelocityZ;}
int16_t CarMotionData::getWorldForwardDirX(){return this->worldForwardDirX;}
int16_t CarMotionData::getWorldForwardDirY(){return this->worldForwardDirY;}
int16_t CarMotionData::getWorldForwardDirZ(){return this->worldForwardDirZ;}
int16_t CarMotionData::getWorldRightDirX(){return this->worldRightDirX;}
int16_t CarMotionData::getWorldRightDirY(){return this->worldRightDirY;}
int16_t CarMotionData::getWorldRightDirZ(){return this->worldRightDirZ;}
float CarMotionData::getGForceLateral(){return this->gForceLateral;}
float CarMotionData::getGForceLongitudinal(){return this->gForceLongitudinal;}
float CarMotionData::getGForceVertical(){return this->gForceVertical;}
float CarMotionData::getYaw(){return this->yaw;}
float CarMotionData::getPitch(){return this->pitch;}
float CarMotionData::getRoll(){return this->roll;}

        void CarMotionData::setWorldPositionX(float worldPositionX){this->worldPositionX = worldPositionX;}
void CarMotionData::setWorldPositionY(float worldPositionY){this->worldPositionY = worldPositionY;}
void CarMotionData::setWorldPositionZ(float worldPositionZ){this->worldPositionZ = worldPositionZ;}
void CarMotionData::setWorldVelocityX(float worldVelocityX){this->worldVelocityX = worldVelocityX;}
void CarMotionData::setWorldVelocityY(float worldVelocityY){this->worldVelocityY = worldVelocityY;}
void CarMotionData::setWorldVelocityZ(float worldVelocityZ){this->worldVelocityZ = worldVelocityZ;}
void CarMotionData::setWorldForwardDirX(int16_t worldForwardDirX){this->worldForwardDirX = worldForwardDirX;}
void CarMotionData::setWorldForwardDirY(int16_t worldForwardDirY){this->worldForwardDirY = worldForwardDirY;}
void CarMotionData::setWorldForwardDirZ(int16_t worldForwardDirZ){this->worldForwardDirZ = worldForwardDirZ;}
void CarMotionData::setWorldRightDirX(int16_t worldRightDirX){this->worldRightDirX = worldRightDirX;}
void CarMotionData::setWorldRightDirY(int16_t worldRightDirY){this->worldRightDirY = worldRightDirY;}
void CarMotionData::setWorldRightDirZ(int16_t worldRightDirZ){this->worldRightDirZ = worldRightDirZ;}
void CarMotionData::setGForceLateral(float gForceLateral){this->gForceLateral = gForceLateral;}
void CarMotionData::setGForceLongitudinal(float gForceLongitudinal){this->gForceLongitudinal = gForceLongitudinal;}
void CarMotionData::setGForceVertical(float gForceVertical){this->gForceVertical = gForceVertical;}
void CarMotionData::setYaw(float yaw){this->yaw = yaw;}
void CarMotionData::setPitch(float pitch){this->pitch = pitch;}
void CarMotionData::setRoll(float roll){this->roll = roll;}

    }
}                    