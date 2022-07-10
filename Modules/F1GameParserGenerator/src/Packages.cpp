#include <Packages.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        void Packages::setName(std::string name){
            this->mName = name;
        }
        std::string Packages::getName(){
            return this->mName;
        }

        void Packages::addField(Fields newField){
            this->mFields.push_back(newField);
        }
        std::vector<Fields> Packages::getFields(){
            return this->mFields;
        }

        int Packages::getSize(){
            return this->mSize;
        }
        void Packages::setSize(int size){
            this->mSize = size;
        }
    }
}