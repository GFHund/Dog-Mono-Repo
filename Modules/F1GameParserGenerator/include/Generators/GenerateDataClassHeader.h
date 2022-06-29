#ifndef __GENERATE_DATA_CLASS_HEADER__
#define __GENERATE_DATA_CLASS_HEADER__

#include <Generators/SourceGenerator.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class GenerateDataClassHeader:public SourceGenerator{
            public:
            virtual std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) override;
            protected:
            void generateF1DataClass(Packages package,std::string outputFolder,std::string gameName);
        };
    }
}

#endif