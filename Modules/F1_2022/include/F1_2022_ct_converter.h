#ifndef 2022
#define 2022
#pragma once

#include <Database.h>

namespace DogGE{
    namespace F1_2022{
        class ConverterCTFormat:public CTelemetry::Converter::ConverterInterface{
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