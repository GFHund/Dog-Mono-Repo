#ifndef __GENERATE_EXCEPTION_SOURCE__
#define __GENERATE_EXCEPTION_SOURCE__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateExceptionSource:public SourceGenerator{
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder);
        };
    }
}
#endif