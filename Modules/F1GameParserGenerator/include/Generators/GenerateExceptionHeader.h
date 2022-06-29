#ifndef __GENERATE_EXCEPTION_HEADER__
#define __GENERATE_EXCEPTION_HEADER__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateExceptionHeader:public SourceGenerator{
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder);
        };
    }
}
#endif