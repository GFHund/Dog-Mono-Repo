#ifndef __PARSER_GENERATOR__
#define __PARSER_GENERATOR__

#include <string>
#include <list>
#include <F1Spec.h>
#include "../vendor/json/json.hpp"

namespace DogGE{
    namespace F1GameParserGenerator{
        class ParserGenerator{
            private:
            std::string mGame;
            std::string mOutput;
            std::list<std::string> mHeaderFileList;
            std::list<std::string> mBodyFileList;

            std::string readFile(std::string path);
            void writeFile(std::string path,std::string content);

            void generateDirStructure();
            void generateEntityClasses();
            void generateF1DataClasses(F1Spec spec);
            void generateF1DataClass(Packages package,std::string srcDir,std::string includeDir,std::string filename);
            public:
            ParserGenerator(std::string game,std::string output);
            void generate();
        };
    }
}

#endif