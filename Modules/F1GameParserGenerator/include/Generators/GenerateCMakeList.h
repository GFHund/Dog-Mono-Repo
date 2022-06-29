#ifndef __GENERATE_C_MAKE_LIST__
#define __GENERATE_C_MAKE_LIST__

#include <F1Spec.h>
#include <Generators/AbstractGenerator.h>
#include <string>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateCMakeList:public AbstractGenerator{
            public:
            void generateCMakeList(F1Spec spec,std::string outputFolder,std::vector<std::string> sourceFiles);
        };
    }
}
#endif