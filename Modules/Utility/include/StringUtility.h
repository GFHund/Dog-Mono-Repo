#ifndef __STRING_UTILITY__
#define __STRING_UTILITY__
#pragma once

#include <string>

namespace DogGE{
    namespace Utility{
        class StringUtility{
            public:
            static std::string base64Encode(std::string str);
            static std::string base64Decode(std::string base64);

            static std::string ucfirst(std::string str);
            static std::string toUppercase(std::string str);
            static std::string toLowercase(std::string str);
            static std::string replaceChar(std::string haystack,char search,char replace);
            static std::string toSnakeCase(std::string str);
            static std::string toCamelCase(std::string str,bool upperCamel);
        };
    }
}


#endif