#include <Generators/SourceGenerator.h>
#include <Exceptions/DataTypeNotFoundException.h>
namespace DogGE{
    namespace F1GameParserGenerator{
        std::string SourceGenerator::getDataType(Fields field,bool function){
            std::string dataType;
            if(field.getType().compare("int") == 0){
                dataType = this->getIntType(field,false);
            } else if(field.getType().compare("uint") == 0){
                dataType = this->getIntType(field,true);
            }else if(field.getType().compare("float") == 0){
                dataType = "float";
            } else if(field.getType().compare("array") == 0){
                
                if(!this->isClass2(field.getItemType())){
                    dataType = this->getDataType2(field.getItemType(),field.getItemTypeSize());
                } else {
                    dataType = field.getItemType();
                }
                if(function){
                    dataType += "*";
                }
            } else {
                dataType = field.getType();
            }
            return dataType;
        }
        std::string SourceGenerator::getDataType2(std::string fieldType,int size){
            std::string dataType;
            if(fieldType.compare("int") == 0){
                dataType = this->getIntType2(fieldType,size,false);
            } else if(fieldType.compare("uint") == 0){
                dataType = this->getIntType2(fieldType,size,true);
            }else if(fieldType.compare("float") == 0){
                dataType = "float";
            } else {
                dataType = fieldType;
            }
            return dataType;
        }
        std::string SourceGenerator::getPostFixVariable(Fields field){
            if(field.getType().compare("array") == 0){
                return "["+std::to_string(field.getSize())+"]";
            } else {
                return "";
            }
        }

        std::string SourceGenerator::getIntType(Fields field,bool unsign){
            switch(field.getSize()){
                case 1: {
                    return (unsign)?"uint8_t":"int8_t";
                }
                case 2:{
                    return (unsign)?"uint16_t":"int16_t";
                }
                case 4:{
                    return (unsign)?"uint32_t":"int32_t";
                }
                case 8:{
                    return (unsign)?"uint64_t":"int64_t";
                }
            }
            throw DataTypeNotFoundException(field.getType(),field.getSize());
        }
        std::string SourceGenerator::getIntType2(std::string fieldType,int size,bool unsign){
            switch(size){
                case 1: {
                    return (unsign)?"uint8_t":"int8_t";
                }
                case 2:{
                    return (unsign)?"uint16_t":"int16_t";
                }
                case 4:{
                    return (unsign)?"uint32_t":"int32_t";
                }
                case 8:{
                    return (unsign)?"uint64_t":"int64_t";
                }
            }
            throw DataTypeNotFoundException(fieldType,size);
        }
        bool SourceGenerator::isClass(Fields field){
            if(this->isArray(field)){
                return (field.getItemType().compare("int") != 0) && 
                (field.getItemType().compare("uint") != 0) &&
                (field.getItemType().compare("float") != 0) &&
                (field.getItemType().compare("double") != 0) &&
                (field.getItemType().compare("char") != 0);
            }
            return (field.getType().compare("int") != 0) && 
                (field.getType().compare("uint") != 0) &&
                (field.getType().compare("float") != 0) &&
                (field.getType().compare("double") != 0) &&
                (field.getType().compare("char") != 0) &&
                (field.getType().compare("array") != 0);
        }
        bool SourceGenerator::isClass2(std::string type){
            return (type.compare("int") != 0) && 
                (type.compare("uint") != 0) &&
                (type.compare("float") != 0) &&
                (type.compare("double") != 0) &&
                (type.compare("char") != 0) &&
                (type.compare("array") != 0);
        }
        bool SourceGenerator::isArray(Fields field){
            return (field.getType().compare("array") == 0);
        }
        bool SourceGenerator::isArray2(std::string type){
            return (type.compare("array") == 0);
        }
    }
}