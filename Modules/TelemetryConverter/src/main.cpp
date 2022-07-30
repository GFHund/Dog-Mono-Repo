#include "../vendor/cxxopts/cxxopts.hpp"
#include <ConverterInterface.h>
#include <Exceptions/ConverterNotFoundException.h>
#include <Exceptions/ConverterNotSuitable.h>

int main(int argc,char** argv){
    cxxopts::Options options("F1GameParserGenerator",
    "Generate Sources for parsing and recording of a Codemaster F1 Game");
    options.add_options()
    ("t,targetType","Specifies target type",cxxopts::value<std::string>())
    ("o,output","Specifies the file name which the converted data will be written",cxxopts::value<std::string>())
    ("i,input","File which will be converted",cxxopts::value<std::string>())
    ("l,list","Lists all available convert types")
    ("h,help","get this Help Test");
    auto result = options.parse(argc,argv);
    if(result.count("help")){
        std::cout << options.help() << std::endl;
        exit(0);
    }
    if(result.count("list")){
        std::cout << "F1_2021: F1 2021 Format" << std::endl;
        std::cout << "F1_2021_ct: F1 2021 to the common type" << std::endl;
        exit(0);
    }
    std::string targetType = result["targetType"].as<std::string>();
    std::string output = result["output"].as<std::string>();
    std::string input = result["input"].as<std::string>();

    CTelemetry::Converter::ConverterInterface* converter = nullptr;

    if(targetType.compare("F1_2021") == 0){
        //
    } else if(targetType.compare("F1_2021_ct")){
        //
    } else {
        throw CTelemetry::Converter::ConverterNotFoundException(targetType);
    }
    if(converter != nullptr){
        if(!converter->canConvert(input)){
            throw CTelemetry::Converter::ConverterNotSuitable();
        } else {
            converter->convert(input,output);
        }
        delete converter;
    }

    
}