#include <ValueType.h>
#include <stdexcept>
#include <Exceptions/ConvertDataTypeException.h>

namespace DogGE{
    namespace Json{

        ValueType::ValueType(std::string value){
            this->mValue = value;
        }

        bool ValueType::isValueType(){
            return true;
        }

        ValueType::DataType ValueType::getType(){
            return this->mType;
        }

        int ValueType::parseToInt(){
            try{
                return std::stoi(this->mValue);
            } catch(std::invalid_argument& e){
                throw ConvertDataTypeException("string","int");
            }
            return 0;
        }
        float ValueType::parseToFloat(){
            try{
                return std::stof(this->mValue);
            } catch(std::invalid_argument& e){
                throw ConvertDataTypeException("string","int");
            }
            return 0.0f;
        }
        std::string ValueType::getData(){
            return this->mValue;
        }
    }
}

