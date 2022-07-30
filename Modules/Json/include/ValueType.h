#ifndef __VALUE_TYPE__
#define __VALUE_TYPE__

#include <AbstractType.h>
#include <string>

namespace DogGE{
    namespace Json{
        class ValueType:public AbstractType{
            public:
            enum DataType{
                TYPE_INT,
                TYPE_STRING,
                TYPE_FLOAT
            };
            private:
            std::string mValue;
            DataType mType;
            public:
            ValueType(std::string value);
            DataType getType();
            bool isValueType() override;
            int parseToInt();
            float parseToFloat();
            std::string getData();
        };
        
    }
}
#endif