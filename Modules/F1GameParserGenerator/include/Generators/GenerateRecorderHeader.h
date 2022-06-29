#ifndef __GENERATE_RECORDER_HEADER__
#define __GENERATE_RECORDER_HEADER__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateRecorderHeader:public SourceGenerator{
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder);
        };
    }
}
#endif