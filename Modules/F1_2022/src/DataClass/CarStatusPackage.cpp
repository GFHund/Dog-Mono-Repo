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

#include <DataClass/CarStatusPackage.h>

namespace DogGE{
    namespace F1_2022{
        Header CarStatusPackage::getHeader(){return this->header;}
CarStatusData* CarStatusPackage::getCarStatus(){return this->carStatus;}

        void CarStatusPackage::setHeader(Header header){this->header = header;}
void CarStatusPackage::setCarStatus(CarStatusData* carStatus){for(int i=0;i<22;i++){
this->carStatus[i] = carStatus[i];
}
}

    }
}                    