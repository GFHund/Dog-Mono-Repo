#ifndef __GENERATE_DATA_ENTITY_SOURCE__
#define __GENERATE_DATA_ENTITY_SOURCE__
#pragma once

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateDataEntitySource: public SourceGenerator{
            private:
            std::string generateRecordEntity(F1Spec spec,std::string outputFolder);
            std::vector<std::string> generatePackagesEntity(F1Spec spec,std::string outputFolder);
            protected:
            std::string getDatabaseType(Fields field);
            public:
            std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
        };
    }
}

#endif 