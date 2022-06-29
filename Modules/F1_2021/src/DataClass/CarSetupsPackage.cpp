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

#include <DataClass/CarSetupsPackage.h>

namespace DogGE{
    namespace F1_2021{
        Header CarSetupsPackage::getHeader(){return this->header;}
CarSetupData* CarSetupsPackage::getCarSetups(){return this->carSetups;}

        void CarSetupsPackage::setHeader(Header header){this->header = header;}
void CarSetupsPackage::setCarSetups(CarSetupData* carSetups){for(int i=0;i<22;i++){
this->carSetups[i] = carSetups[i];
}
}

    }
}                    