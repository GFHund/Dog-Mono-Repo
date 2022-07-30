#include <PropertyType.h>
namespace DogGE{
    namespace Json{
        PropertyType::PropertyType(std::string name){
            this->mPropertiesName = name;
        }

        std::string PropertyType::getName(){
            return this->mPropertiesName;
        }

        bool PropertyType::isPropertyType(){
            return true;
        }
    }
}