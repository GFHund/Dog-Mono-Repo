#include <iostream>
#include "../vendor/cxxopts/cxxopts.hpp"
#include <ParserGenerator.h>

int main(int argc,char** argv){
    cxxopts::Options options("F1GameParserGenerator",
    "Generate Sources for parsing and recording of a Codemaster F1 Game");
    options.add_options()
    ("g,game","Specifies the F1 Game",cxxopts::value<std::string>())
    ("o,output","Specifies the dir name which the generated sources will be put into",cxxopts::value<std::string>())
    ("h,help","get this Help Test");
    auto result = options.parse(argc,argv);
    if(result.count("help")){
        std::cout << options.help() << std::endl;
        exit(0);
    }
    std::string game = result["game"].as<std::string>();
    std::string output = result["output"].as<std::string>();
    DogGE::F1GameParserGenerator::ParserGenerator generator(game,output);
    generator.generate();
    return 0;
}