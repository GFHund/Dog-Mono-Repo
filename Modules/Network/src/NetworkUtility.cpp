#include <NetworkUtility.h>


namespace DogGE{
    namespace Network{
        std::string NetworkUtility::encodeStringToBase64(std::string string){
            int padding = (int)(3-(string.size() % 3));
            if(padding == 1){
                string += (char)0x00;
            } else if(padding == 2){
                string += (char)0x00;
                string += (char)0x00;
            } else {
                padding = 0;
            }
            std::string ret = "";
            for(int i=0;i<string.size();i+=3){
                bool end = false;
                if(string.size() <= i+3){
                    end = true;
                }
                uint32_t concatByte = string[i] << 16 | string[i+1] << 8 | string[i+2];
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