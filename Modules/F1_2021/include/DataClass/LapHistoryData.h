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

#ifndef __LAP_HISTORY_DATA__
#define __LAP_HISTORY_DATA__
#pragma once

#include <stdint.h>


namespace DogGE{
    namespace F1_2021{
        class LapHistoryData{
            private:
            uint32_t lapTimeInMS;
uint16_t sector1TimeInMs;
uint16_t sector2TimeInMs;
uint16_t sector3TimeInMs;
uint8_t lapValidBitFlags;

            public:
            void setLapTimeInMS(uint32_t lapTimeInMS);
void setSector1TimeInMs(uint16_t sector1TimeInMs);
void setSector2TimeInMs(uint16_t sector2TimeInMs);
void setSector3TimeInMs(uint16_t sector3TimeInMs);
void setLapValidBitFlags(uint8_t lapValidBitFlags);

            uint32_t getLapTimeInMS();
uint16_t getSector1TimeInMs();
uint16_t getSector2TimeInMs();
uint16_t getSector3TimeInMs();
uint8_t getLapValidBitFlags();

        };
    }
}

#endif                                