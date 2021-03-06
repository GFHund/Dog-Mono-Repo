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

#ifndef __CAR_TELEMETRY_PACKAGE__
#define __CAR_TELEMETRY_PACKAGE__
#pragma once

#include <stdint.h>
#include <DataClass/Header.h>
#include <DataClass/CarTelemetryData.h>


namespace DogGE{
    namespace F1_2022{
        class CarTelemetryPackage{
            private:
            Header header;
CarTelemetryData carTelemetry[22];
uint8_t mfdPanelIndex;
uint8_t mfdPanelIndexSecondaryPlayer;
int8_t suggestedGear;

            public:
            void setHeader(Header header);
void setCarTelemetry(CarTelemetryData* carTelemetry);
void setMfdPanelIndex(uint8_t mfdPanelIndex);
void setMfdPanelIndexSecondaryPlayer(uint8_t mfdPanelIndexSecondaryPlayer);
void setSuggestedGear(int8_t suggestedGear);

            Header getHeader();
CarTelemetryData* getCarTelemetry();
uint8_t getMfdPanelIndex();
uint8_t getMfdPanelIndexSecondaryPlayer();
int8_t getSuggestedGear();

        };
    }
}

#endif                                