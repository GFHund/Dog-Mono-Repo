#ifndef __PARSE_JSON__
#define __PARSE_JSON__

#include <string>
#include <ArrayTree.h>
#include <AbstractType.h>

namespace DogGE{
    namespace Json{
        class JsonParser{
            public:
            DogGE::Tree::ArrayTree<AbstractType*> parse(std::string jsonString);
        };
    }
}

#endif