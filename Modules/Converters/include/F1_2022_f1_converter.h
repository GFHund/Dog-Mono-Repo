#ifndef __CONVERTER_F1_2022__
#define __CONVERTER_F1_2022__
#pragma once

#include <Database.h>
#include <ConverterInterface.h>

namespace DogGE{
    namespace Converters{
        class ConverterStandardFormat:public CTelemetry::Converter::ConverterInterface{
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