#ifndef __NETWORK_UTILITY__
#define __NETWORK_UTILITY__
#pragma once

#include <string>
#include <array>

namespace DogGE{
    namespace Network{
        class NetworkUtility{
            public:
            //template<std::size_t T>
            //static std::string encodeDataToBase64(std::array<char,T> data);
            static std::string encodeStringToBase64(std::string string);
        };
    }
}

#endif