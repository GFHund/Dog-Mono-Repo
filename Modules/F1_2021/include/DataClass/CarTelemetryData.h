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

#ifndef __CAR_TELEMETRY_DATA__
#define __CAR_TELEMETRY_DATA__
#pragma once

#include <stdint.h>


namespace DogGE{
    namespace F1_2021{
        class CarTelemetryData{
            private:
            uint16_t speed;
float throttle;
float steer;
float brake;
uint8_t clutch;
int8_t gear;
uint16_t engineRPM;
uint8_t drs;
uint8_t revLightsPercent;
uint16_t revLightsBitValue;
uint16_t brakesTemperatureRL;
uint16_t brakesTemperatureRR;
uint16_t brakesTemperatureFL;
uint16_t brakesTemperatureFR;
uint8_t tyreSurfaceTemperatureRL;
uint8_t tyreSurfaceTemperatureRR;
uint8_t tyreSurfaceTemperatureFL;
uint8_t tyreSurfaceTemperatureFR;
uint8_t tyreInnerTemperatureRL;
uint8_t tyreInnerTemperatureRR;
uint8_t tyreInnerTemperatureFL;
uint8_t tyreInnerTemperatureFR;
uint16_t engineTemperature;
float tyresPressureRL;
float tyresPressureRR;
float tyresPressureFL;
float tyresPressureFR;
uint8_t surfaceTypeRL;
uint8_t surfaceTypeRR;
uint8_t surfaceTypeFL;
uint8_t surfaceTypeFR;

            public:
            void setSpeed(uint16_t speed);
void setThrottle(float throttle);
void setSteer(float steer);
void setBrake(float brake);
void setClutch(uint8_t clutch);
void setGear(int8_t gear);
void setEngineRPM(uint16_t engineRPM);
void setDrs(uint8_t drs);
void setRevLightsPercent(uint8_t revLightsPercent);
void setRevLightsBitValue(uint16_t revLightsBitValue);
void setBrakesTemperatureRL(uint16_t brakesTemperatureRL);
void setBrakesTemperatureRR(uint16_t brakesTemperatureRR);
void setBrakesTemperatureFL(uint16_t brakesTemperatureFL);
void setBrakesTemperatureFR(uint16_t brakesTemperatureFR);
void setTyreSurfaceTemperatureRL(uint8_t tyreSurfaceTemperatureRL);
void setTyreSurfaceTemperatureRR(uint8_t tyreSurfaceTemperatureRR);
void setTyreSurfaceTemperatureFL(uint8_t tyreSurfaceTemperatureFL);
void setTyreSurfaceTemperatureFR(uint8_t tyreSurfaceTemperatureFR);
void setTyreInnerTemperatureRL(uint8_t tyreInnerTemperatureRL);
void setTyreInnerTemperatureRR(uint8_t tyreInnerTemperatureRR);
void setTyreInnerTemperatureFL(uint8_t tyreInnerTemperatureFL);
void setTyreInnerTemperatureFR(uint8_t tyreInnerTemperatureFR);
void setEngineTemperature(uint16_t engineTemperature);
void setTyresPressureRL(float tyresPressureRL);
void setTyresPressureRR(float tyresPressureRR);
void setTyresPressureFL(float tyresPressureFL);
void setTyresPressureFR(float tyresPressureFR);
void setSurfaceTypeRL(uint8_t surfaceTypeRL);
void setSurfaceTypeRR(uint8_t surfaceTypeRR);
void setSurfaceTypeFL(uint8_t surfaceTypeFL);
void setSurfaceTypeFR(uint8_t surfaceTypeFR);

            uint16_t getSpeed();
float getThrottle();
float getSteer();
float getBrake();
uint8_t getClutch();
int8_t getGear();
uint16_t getEngineRPM();
uint8_t getDrs();
uint8_t getRevLightsPercent();
uint16_t getRevLightsBitValue();
uint16_t getBrakesTemperatureRL();
uint16_t getBrakesTemperatureRR();
uint16_t getBrakesTemperatureFL();
uint16_t getBrakesTemperatureFR();
uint8_t getTyreSurfaceTemperatureRL();
uint8_t getTyreSurfaceTemperatureRR();
uint8_t getTyreSurfaceTemperatureFL();
uint8_t getTyreSurfaceTemperatureFR();
uint8_t getTyreInnerTemperatureRL();
uint8_t getTyreInnerTemperatureRR();
uint8_t getTyreInnerTemperatureFL();
uint8_t getTyreInnerTemperatureFR();
uint16_t getEngineTemperature();
float getTyresPressureRL();
float getTyresPressureRR();
float getTyresPressureFL();
float getTyresPressureFR();
uint8_t getSurfaceTypeRL();
uint8_t getSurfaceTypeRR();
uint8_t getSurfaceTypeFL();
uint8_t getSurfaceTypeFR();

        };
    }
}

#endif                                