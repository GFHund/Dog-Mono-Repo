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
            int mSize;
            public:
            void setName(std::string name);
            std::string getName();

            void addField(Fields newField);
            std::vector<Fields> getFields();

            int getSize();
            void setSize(int size);
        };
    }
}

#endif