#ifndef {{&DEFINE_NAME}}
#define {{&DEFINE_NAME}}
#pragma once

#include <Database.h>

namespace DogGE{
    namespace {{&NAMESPACE_NAME}}{
        class {{&CLASS_NAME}}:public CTelemetry::Converter::ConverterInterface{
            private:
            protected:
            void insertDataPoint(DogGE::Database::Database* input,DogGE::Database::Database* output,int offset);
            public:
            virtual bool canConvert(std::string inputFile) override;
            virtual void convert(std::string input,std::string output) override;
        };
    }
}
#endif