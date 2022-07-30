#include <AbstractType.h>

namespace DogGE{
    namespace Json{
        bool AbstractType::isArrayType(){
            return false;
        }
        bool AbstractType::isObjectType(){
            return false;
        }
        bool AbstractType::isPropertyType(){
            return false;
        }
        bool AbstractType::isValueType(){
            return false;
        }
    }
}