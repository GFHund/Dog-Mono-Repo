#ifndef __GENERATE_CONVERTER_SOURCE__
#define __GENERATE_CONVERTER_SOURCE__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateConverterSource:public SourceGenerator{
            private:
            std::string generateCtConverter(F1Spec spec,std::string outputFolder);
            std::string generateF1StandardFormat(F1Spec spec,std::string outputFolder);
            public:
            virtual std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
        };
    }
}

#endif