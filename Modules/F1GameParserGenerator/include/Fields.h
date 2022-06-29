#ifndef __FIELDS__
#define __FIELDS__
#pragma once

#include <string>

namespace DogGE{
    namespace F1GameParserGenerator{
        class Fields{
            private:
            std::string mName;
            std::string mType;
            int mSize;
            std::string mItemType;
            int mItemTypeSize;
            public:
            void setName(std::string name);
            std::string getName();

            void setType(std::string type);
            std::string getType();

            void setSize(int size);
            int getSize();

            std::string getItemType();
            void setItemType(std::string itemType);

            int getItemTypeSize();
            void setItemTypeSize(int itemTypeSize);
        };
    }
}

#endif