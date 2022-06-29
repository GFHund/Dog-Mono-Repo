#include <F1SpecBuilder.h>
#include <iostream>
#include <fstream>
namespace DogGE{
    namespace F1GameParserGenerator{
        F1Spec F1SpecBuilder::build(std::string game){
            std::string jsonFilePath = "F1Spec/";
            jsonFilePath += game;
            jsonFilePath += ".json";
            nlohmann::json j = F1SpecBuilder::readJson(jsonFilePath);
            return F1SpecBuilder::getSpecification(j);
        }

        nlohmann::json F1SpecBuilder::readJson(std::string path){
            std::ifstream ifs(path.c_str());
            nlohmann::json j;
            ifs >> j;
            return j;
        }

        F1Spec F1SpecBuilder::getSpecification(nlohmann::json j){
            F1Spec spec;
            for(auto [key,value]: j.items()){
                if(key.compare("name") == 0){
                    spec.setName(value);
                }
                else if(key.compare("headerName") == 0){
                    spec.setHeaderName(value);
                }
                else if(key.compare("packagesMapping") == 0){
                    for(auto [packageID,packageName]:value.items()){
                        spec.addPackagesMapping(std::stoi(packageID),packageName);
                    }
                }
                else if(key.compare("packages") == 0){
                    for(auto [packageName,packageValue]:value.items()){
                        Packages package;
                        package.setName(packageName);
                        auto iterFields = packageValue.find("fields");
                        if(iterFields != packageValue.end()){
                            for(auto fieldIter:*iterFields){
                                Fields field;
                                auto iterName = fieldIter.find("name");
                                auto iterType = fieldIter.find("type");
                                auto iterSize = fieldIter.find("size");
                                auto iterItemType = fieldIter.find("itemType");
                                auto iterItemSize = fieldIter.find("itemTypeSize");
                                if(iterName != fieldIter.end()){
                                    field.setName(*iterName);
                                }
                                if(iterType != fieldIter.end()){
                                    field.setType(*iterType);
                                }
                                if(iterSize != fieldIter.end()){
                                    field.setSize(*iterSize);
                                }
                                if(iterItemType != fieldIter.end()){
                                    field.setItemType(*iterItemType);
                                }
                                if(iterItemSize != fieldIter.end()){
                                    field.setItemTypeSize(*iterItemSize);
                                }
                                package.addField(field);
                            }
                        }
                        spec.addPackage(package);
                    }
                }
            }
            return spec;
        }
    }
}