#ifndef __GENERATE_DATA_ENTITY_HEADER__
#define __GENERATE_DATA_ENTITY_HEADER__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateDataEntityHeader: public SourceGenerator{
            private:
            void generateRecordEntity(F1Spec spec,std::string outputFolder);
            void generatePackagesEntity(F1Spec spec,std::string outputFolder);
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
        };
    }
}

#endif 