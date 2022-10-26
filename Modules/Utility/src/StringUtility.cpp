#include <StringUtility.h>

namespace DogGE{
    namespace Utility{
        std::string StringUtility::base64Encode(std::string string){
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
                        printf("j: %i\n",j);
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
        std::string StringUtility::base64Decode(std::string base64){
            return "";
        }

        std::string StringUtility::ucfirst(std::string str){
            if(str[0] >= 'a' && str[0] <= 'z'){
                str[0] = str[0] - ('a' - 'A');
            }
            return str;
        }

        std::string StringUtility::toUppercase(std::string str){
            char diffLowerUpperCase = 'a' - 'A';
            for(int i=0;i<str.size();i++){
                if(str[i] >= 'a' && str[i] <= 'z'){
                    str[i] = str[i] - diffLowerUpperCase;
                }
            }
            return str;
        }
        std::string StringUtility::toLowercase(std::string str){
            char diffLowerUpperCase = 'a' - 'A';
            for(int i=0;i<str.size();i++){
                if(str[i] >= 'A' && str[i] <= 'Z'){
                    str[i] = str[i] + diffLowerUpperCase;
                }
            }
            return str;
        }
        std::string StringUtility::replaceChar(std::string haystack,char search,char replace){
            for(int i=0;i<haystack.size();i++){
                if(haystack[i] == search){
                    haystack[i] = replace;
                }
            }
            return haystack;
        }
        std::string StringUtility::toSnakeCase(std::string str){
            std::string ret;
            char last = 0;
            int pointer = 0;
            char diffLowerUpperCase = 'a' - 'A';
            for(int i=0;i<str.size();i++){
                if(str[i] == '-' || str[i] == ' '){
                    last = str[i];
                    ret += '_';
                    continue;
                }
                if(last >= 'a' && last <= 'z' && str[i] >= 'A' && str[i] <= 'Z'){
                    last = str[i];
                    ret += '_';
                }
                if(str[i] >= 'A' && str[i] <= 'Z'){
                    ret += str[i] + diffLowerUpperCase;
                    last = str[i];
                } else {
                    last = str[i];
                    ret += str[i];
                }
            }
            return ret;
        }
        std::string StringUtility::toCamelCase(std::string str,bool upperCamel){
            std::string ret;
            bool toUpper = upperCamel;
            char diffLowerUpperCase = 'a' - 'A';
            for(int i=0;i<str.size();i++){
                if(str[i] == '-' || str[i] == ' ' || str[i] == '_'){
                    toUpper = true;
                    continue;
                }
                if(str[i] >= 'a' && str[i] <= 'z' && toUpper){
                    ret += str[i] - diffLowerUpperCase;
                    toUpper = false;
                } else {
                    ret += str[i];
                }
            }
            return ret;
        }
        
        std::string StringUtility::trim(std::string str,char c){
            int from=-1,to=-1;
            for(int i=0;i<str.size();i++){
                if(str[i] != c){
                    from = i;
                    break;
                }
            }
            for(int i=str.size()-1;i>0;i--){
                if(str[i] != c){
                    to = i;
                    break;
                }
            }
            to++;
            return str.substr(from,to-from);
        }
    }
}