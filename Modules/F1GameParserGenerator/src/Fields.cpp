#include <Fields.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        void Fields::setName(std::string name){
            this->mName = name;
        }
        std::string Fields::getName(){
            return this->mName;
        }

        void Fields::setType(std::string type){
            this->mType = type;
        }
        std::string Fields::getType(){
            return this->mType;
        }

        void Fields::setSize(int size){
            this->mSize = size;
        }
        int Fields::getSize(){
            return this->mSize;
        }

        std::string Fields::getItemType(){
            return this->mItemType;
        }
        void Fields::setItemType(std::string itemType){
            this->mItemType = itemType;
        }

        int Fields::getItemTypeSize(){
            return this->mItemTypeSize;
        }
        void Fields::setItemTypeSize(int itemTypeSize){
            this->mItemTypeSize = itemTypeSize;
        }
    }
}