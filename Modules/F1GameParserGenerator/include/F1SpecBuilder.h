#ifndef __F1_SPEC_BUILDER__
#define __F1_SPEC_BUILDER__
#pragma once

#include <F1Spec.h>
#include "../vendor/json/json.hpp"

namespace DogGE{
    namespace F1GameParserGenerator{
        class F1SpecBuilder{
            protected:
            static F1Spec getSpecification(nlohmann::json j);
            static nlohmann::json readJson(std::string path);
            public:
            static F1Spec build(std::string game);
            
        };
        
    }
}
#endif