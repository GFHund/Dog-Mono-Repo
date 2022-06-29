#ifndef __GENERATE_CONVERTER_HEADER__
#define __GENERATE_CONVERTER_HEADER__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateConverterHeader:public SourceGenerator{
            private:
            void generateCtConverter(F1Spec spec,std::string outputFolder);
            void generateF1StandardFormat(F1Spec spec,std::string outputFolder);
            public:
            virtual std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
        };
    }
}

#endif