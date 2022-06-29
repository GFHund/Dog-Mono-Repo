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

#ifndef __MARSHAL_ZONE__
#define __MARSHAL_ZONE__
#pragma once

#include <stdint.h>


namespace DogGE{
    namespace F1_2022{
        class MarshalZone{
            private:
            float zoneStart;
int8_t zoneFlag;

            public:
            void setZoneStart(float zoneStart);
void setZoneFlag(int8_t zoneFlag);

            float getZoneStart();
int8_t getZoneFlag();

        };
    }
}

#endif                                