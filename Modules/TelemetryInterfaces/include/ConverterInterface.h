#ifndef __CONVERTER_INTERFACE__
#define __CONVERTER_INTERFACE__
#pragma once

namespace CTelemetry{
    namespace Converter{
        class ConverterInterface{
            public:
            virtual bool canConvert(std::string inputFile) = 0;
            virtual void convert(std::string input,std::string output) = 0;
        };
    }
}
#endif