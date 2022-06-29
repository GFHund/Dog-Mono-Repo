#ifndef __GENERATE_DATA_CLASS_SOURCE__
#define __GENERATE_DATA_CLASS_SOURCE__

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateDataClassSource:public SourceGenerator{
            public:
            virtual std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
            protected:
            std::string generateF1DataClass(Packages package,std::string outputFolder,std::string gameName);
        };
    }
}

#endif