#ifndef __NETWORK_UTILITY__
#define __NETWORK_UTILITY__
#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>

namespace DogGE{
    namespace Network{
        class NetworkUtility{
            public:
            template<std::size_t T>
            static std::string encodeDataToBase64(std::array<unsigned char,T> data);
            static std::string encodeStringToBase64(std::string string);
        };

        template <std::size_t T>
        std::string NetworkUtility::encodeDataToBase64(std::array<unsigned char,T> data){
            std::vector<unsigned char> internalArr;
            for(auto iter: data){
                internalArr.push_back(iter);
            }

            int padding = (int)(3 - (T % 3));
            if(padding == 1){
                internalArr.push_back((char)0x00);
            } else if(padding == 2){
                internalArr.push_back((char)0x00);
                internalArr.push_back((char)0x00);
            } else {
                padding = 0;
            }
            std::string ret = "";
            for(int i=0;i<internalArr.size();i+=3){
                bool end = false;
                if(internalArr.size() <= i+3){
                    end = true;
                }
                uint32_t concatByte = internalArr[i] << 16 | internalArr[i+1] << 8 | internalArr[i+2];
                unsigned char sixBitBlock[4];
                for(int j=0;j<24;j+=6){
                    int index = j/6;
                    uint32_t valueBlock = concatByte & (0x3f << (18-j));    
                    sixBitBlock[index] = (valueBlock >> (18-j));
                }
                for(int j = 0;j<4;j++){
                    if(end){
                        if(padding == 2 && j > 1){
                            break;
                        }
                        if(padding == 1 && j >= 3){
                            break;
                        }
                    }
                    
                    if(sixBitBlock[j] <= 25){
                        ret += 0x41 + sixBitBlock[j];
                    } else if(sixBitBlock[j] > 25 && sixBitBlock[j] <= 51){
                        ret += 0x61 + (sixBitBlock[j] - 26);
                    } else if(sixBitBlock[j] > 51 && sixBitBlock[j] <= 61){
                        ret += 0x30 + (sixBitBlock[j] - 52);
                    } else if(sixBitBlock[j] == 62){
                        ret += '+';
                    } else if(sixBitBlock[j] == 63){
                        ret += '/';
                    }
                }
            }
            for(int i = 0;i< padding;i++){
                ret += '=';
            }
            return ret;
        }
    }
}

#endif