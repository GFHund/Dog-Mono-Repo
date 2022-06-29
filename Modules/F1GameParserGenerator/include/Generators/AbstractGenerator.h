#ifndef __ABSTRACT_GENERATOR__
#define __ABSTRACT_GENERATOR__

#include <string>
#include "../vendor/json/json.hpp"
#include "../vendor/mustache/mustache.hpp"

namespace DogGE{
    namespace F1GameParserGenerator{
        class AbstractGenerator{
            protected:
            void renderFile(std::string inputFile,std::string outputFile,kainjow::mustache::data data);
            void writeFile(std::string path,std::string content);
            std::string readFile(std::string path);
        };
    }
}

#endif