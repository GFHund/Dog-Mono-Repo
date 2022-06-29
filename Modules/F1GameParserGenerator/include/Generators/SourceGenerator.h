#ifndef __SOURCE_GENERATOR__
#define __SOURCE_GENERATOR__
#pragma once

#include <Generators/AbstractGenerator.h>
#include <F1Spec.h>
#include <string>
#include <vector>

namespace DogGE{
    namespace F1GameParserGenerator{
        class SourceGenerator:public AbstractGenerator{
            protected:
            std::string getDataType(Fields field,bool function = false);
            std::string getDataType2(std::string fieldType,int size);
            std::string getPostFixVariable(Fields field);
            std::string getIntType(Fields field,bool unsign);
            std::string getIntType2(std::string fieldType,int size,bool unsign);
            bool isClass(Fields field);
            bool isClass2(std::string type);
            bool isArray(Fields field);
            bool isArray2(std::string type);
            public:
            virtual std::vector<std::string> generateSource(F1Spec spec,std::string outputFolder) = 0;
        };
    }
}

#endif