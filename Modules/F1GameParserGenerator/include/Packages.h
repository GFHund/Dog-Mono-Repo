#ifndef __PACKAGES__
#define __PACKAGES__
#pragma once

#include <string>
#include <vector>
#include <Fields.h>


namespace DogGE{
    namespace F1GameParserGenerator{
        class Packages{
            private:
            std::string mName;
            std::vector<Fields> mFields;
            public:
            void setName(std::string name);
            std::string getName();

            void addField(Fields newField);
            std::vector<Fields> getFields();
        };
    }
}

#endif