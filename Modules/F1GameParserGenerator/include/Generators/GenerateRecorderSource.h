#ifndef __GENERATE_RECORDER_SOURCE__
#define __GENERATE_RECORDER_SOURCE__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateRecorderSource:public SourceGenerator{
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder);
        };
    }
}
#endif