#ifndef __PROPERTIES_TYPE__
#define __PROPERTIES_TYPE__

#include <AbstractType.h>
#include <string>

namespace DogGE{
    namespace Json{
        class PropertyType: public AbstractType{
            private:
            std::string mPropertiesName;

            public:
            PropertyType(std::string propertiesName);
            std::string getName();
            bool isPropertyType() override;
         
        };
    }
}

#endif