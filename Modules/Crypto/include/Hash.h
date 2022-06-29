#ifndef __HASH__
#define __HASH__
#pragma once
#include <string>

namespace DogGE{
    namespace Crypto{
        class Hash{
            public:
            static std::string sha1(std::string message);
        };
    }
}
#endif