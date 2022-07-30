#ifndef __ABSTRACT_TYPE__
#define __ABSTRACT_TYPE__

namespace DogGE{
    namespace Json{
        class AbstractType{
            public:
            virtual bool isArrayType();
            virtual bool isObjectType();
            virtual bool isPropertyType();
            virtual bool isValueType();

        };
    }
}

#endif