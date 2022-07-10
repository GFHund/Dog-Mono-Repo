#ifndef __F1_SPEC_VALIDATOR__
#define __F1_SPEC_VALIDATOR__

#include <F1Spec.h>
#include <Fields.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class F1SpecValidator{
            static bool isStandardType(std::string type);
            static int getSize(F1Spec spec,Fields field);
            public:
            static bool validateSpecification(F1Spec spec);
        };
    }
}
#endif 