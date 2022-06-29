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

#ifndef __MOTION_PACKAGE__
#define __MOTION_PACKAGE__
#pragma once

#include <stdint.h>
#include <DataClass/Header.h>
#include <DataClass/CarMotionData.h>


namespace DogGE{
    namespace F1_2021{
        class MotionPackage{
            private:
            Header header;
CarMotionData carMotionData[22];
float suspensionPosition[4];
float suspensionVelocity[4];
float suspensionAcceleration[4];
float wheelSpeed[4];
float wheelSlip[4];
float localVelocityX;
float localVelocityY;
float localVelocityZ;
float angularVelocityX;
float angularVelocityY;
float angularVelocityZ;
float angularAccelerationX;
float angularAccelerationY;
float angularAccelerationZ;
float frontWheelsAngle;

            public:
            void setHeader(Header header);
void setCarMotionData(CarMotionData* carMotionData);
void setSuspensionPosition(float* suspensionPosition);
void setSuspensionVelocity(float* suspensionVelocity);
void setSuspensionAcceleration(float* suspensionAcceleration);
void setWheelSpeed(float* wheelSpeed);
void setWheelSlip(float* wheelSlip);
void setLocalVelocityX(float localVelocityX);
void setLocalVelocityY(float localVelocityY);
void setLocalVelocityZ(float localVelocityZ);
void setAngularVelocityX(float angularVelocityX);
void setAngularVelocityY(float angularVelocityY);
void setAngularVelocityZ(float angularVelocityZ);
void setAngularAccelerationX(float angularAccelerationX);
void setAngularAccelerationY(float angularAccelerationY);
void setAngularAccelerationZ(float angularAccelerationZ);
void setFrontWheelsAngle(float frontWheelsAngle);

            Header getHeader();
CarMotionData* getCarMotionData();
float* getSuspensionPosition();
float* getSuspensionVelocity();
float* getSuspensionAcceleration();
float* getWheelSpeed();
float* getWheelSlip();
float getLocalVelocityX();
float getLocalVelocityY();
float getLocalVelocityZ();
float getAngularVelocityX();
float getAngularVelocityY();
float getAngularVelocityZ();
float getAngularAccelerationX();
float getAngularAccelerationY();
float getAngularAccelerationZ();
float getFrontWheelsAngle();

        };
    }
}

#endif                                