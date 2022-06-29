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

#ifndef __LAP_DATA_PACKAGE__
#define __LAP_DATA_PACKAGE__
#pragma once

#include <stdint.h>
#include <DataClass/Header.h>
#include <DataClass/LapData.h>


namespace DogGE{
    namespace F1_2021{
        class LapDataPackage{
            private:
            Header header;
LapData lapData[22];

            public:
            void setHeader(Header header);
void setLapData(LapData* lapData);

            Header getHeader();
LapData* getLapData();

        };
    }
}

#endif                                