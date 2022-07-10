#include <ParserGenerator.h>
#include <StringUtility.h>
#include <VectorUtility.h>
#include <filesystem>
#include <fstream>

#include "../vendor/mustache/mustache.hpp"

#include <Packages.h>
#include <Fields.h>
#include <F1SpecBuilder.h>
#include <F1SpecValidator.h>
#include <Exceptions/FileNotFoundException.h>
#include <Exceptions/PackageNotFoundException.h>

#include <Generators/GenerateDataClassHeader.h>
#include <Generators/GenerateDataClassSource.h>
#include <Generators/GenerateDataEntityHeader.h>
#include <Generators/GenerateDataEntitySource.h>
#include <Generators/GenerateRecorderHeader.h>
#include <Generators/GenerateRecorderSource.h>
#include <Generators/GenerateConverterHeader.h>
#include <Generators/GenerateConverterSource.h>
#include <Generators/GenerateExceptionHeader.h>
#include <Generators/GenerateExceptionSource.h>
#include <Generators/GenerateCMakeList.h>
#include <VectorUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        ParserGenerator::ParserGenerator(std::string game,std::string output){
            this->mGame = game;
            this->mOutput = output;
        }
        void ParserGenerator::generate(){
            this->generateDirStructure();
            F1Spec spec = F1SpecBuilder::build(this->mGame);

            if(!F1SpecValidator::validateSpecification(spec)){
                return;
            }
            //this->generateF1DataClasses(spec);
            GenerateDataClassHeader DataHeader;
            DataHeader.generateSource(spec,this->mOutput);
            
            GenerateDataClassSource DataSource;
            std::vector<std::string> sourceFiles = DataSource.generateSource(spec,this->mOutput);

            GenerateDataEntityHeader dataEntityHeader;
            dataEntityHeader.generateSource(spec,this->mOutput);

            GenerateDataEntitySource dataEntitySource;
            std::vector<std::string> sourceFiles2 = dataEntitySource.generateSource(spec,this->mOutput);

            GenerateRecorderHeader recorderHeader;
            recorderHeader.generateSource(spec,this->mOutput);

            GenerateRecorderSource recorderSource;
            std::vector<std::string> sourceFiles3 = recorderSource.generateSource(spec,this->mOutput);

            GenerateConverterHeader converterHeader;
            converterHeader.generateSource(spec,this->mOutput);

            GenerateConverterSource converterSource;
            std::vector<std::string> sourceFiles5 = converterSource.generateSource(spec,this->mOutput);


            GenerateExceptionHeader exceptionHeader;
            exceptionHeader.generateSource(spec,this->mOutput);
            
            GenerateExceptionSource exceptionSource;
            std::vector<std::string> sourceFiles4 = exceptionSource.generateSource(spec,this->mOutput);

            sourceFiles = DogGE::Utility::VectorUtility<std::string>(sourceFiles).merge(sourceFiles2);
            sourceFiles = DogGE::Utility::VectorUtility<std::string>(sourceFiles).merge(sourceFiles3);
            sourceFiles = DogGE::Utility::VectorUtility<std::string>(sourceFiles).merge(sourceFiles4);
            //sourceFiles = DogGE::Utility::VectorUtility<std::string>(sourceFiles).merge(sourceFiles5);
            
            GenerateCMakeList cmakeList;
            cmakeList.generateCMakeList(spec,this->mOutput,sourceFiles);
            std::cout << "------- Generation End ----------" << std::endl;
        }
        
        
        std::string ParserGenerator::readFile(std::string path){
            std::ifstream ifs(path.c_str());
            if(!ifs.is_open()){
                throw FileNotFoundException(path);
            }
            ifs.seekg(0,ifs.end);
            int length = ifs.tellg();
            ifs.seekg(0,ifs.beg);
            char* buffer = new char[length+1];
            ifs.read(buffer,length);
            ifs.close();
            buffer[length] = '\0';
            std::string file = std::string(buffer);
            delete[] buffer;
            return file;
        }
        void ParserGenerator::writeFile(std::string path,std::string content){
            std::ofstream ofs(path.c_str());
            ofs << content;
            ofs.close();
        }

        void ParserGenerator::generateDirStructure(){
            std::string srcDir = this->mOutput;
            std::string includeDir = this->mOutput;

            std::string srcExceptionDir = this->mOutput;
            std::string includeExceptionDir = this->mOutput;

            std::string srcDataClassDir = this->mOutput;
            std::string includeDataClassDir = this->mOutput;

            std::string srcEntityClassDir = this->mOutput;
            std::string includeEntityClassDir = this->mOutput;
            
            srcDir += "/src"; 
            includeDir += "/include";

            srcExceptionDir += "/src/Exceptions";
            includeExceptionDir += "/include/Exceptions";

            srcDataClassDir += "/src/DataClass";
            includeDataClassDir += "/include/DataClass";

            srcEntityClassDir += "/src/Entity";
            includeEntityClassDir += "/include/Entity";
            
            std::filesystem::create_directory(this->mOutput);
            std::filesystem::create_directory(srcDir);
            std::filesystem::create_directory(includeDir);

            std::filesystem::create_directory(srcExceptionDir);
            std::filesystem::create_directory(includeExceptionDir);

            std::filesystem::create_directory(srcDataClassDir);
            std::filesystem::create_directory(includeDataClassDir);

            std::filesystem::create_directory(srcEntityClassDir);
            std::filesystem::create_directory(includeEntityClassDir);
        }
        void generateEntityClasses(){

        }
        void ParserGenerator::generateF1DataClasses(F1Spec spec){
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> srcFiles;
            std::string srcDir = this->mOutput;
            std::string includeDir = this->mOutput;
            srcDir += "/src"; 
            includeDir += "/include";
            for(auto iter:packages){
                std::string filename = iter.getName();
                generateF1DataClass(iter,srcDir,includeDir,filename);
                filename = "src/"+filename+".cpp";
                srcFiles.push_back(filename);
            }

            kainjow::mustache::data cMakeListData;
            std::string cMakeListSources = "";
            for(auto iter: srcFiles){
                cMakeListSources += iter;
                cMakeListSources += "\n";
            }
            cMakeListData.set("GAME_NAME",spec.getName());
            cMakeListData.set("SOURCES",cMakeListSources);
            std::string cMakeListsFile = this->readFile("template/CMakeListsTemplate.txt");
            kainjow::mustache::mustache cMakeListsTemplate(cMakeListsFile);
            std::string cMakeListRenderResult = cMakeListsTemplate.render(cMakeListData);
            std::string cmakeFile = this->mOutput + "/CMakeLists.txt";
            this->writeFile(cmakeFile,cMakeListRenderResult);
        }
        void ParserGenerator::generateF1DataClass(Packages package,std::string srcDir,std::string includeDir,std::string filename){
            std::string headerFile = this->readFile("template/F1DataClassTemplate.h");
            std::string bodyFile = this->readFile("template/F1DataClassTemplate.cpp");
            std::string f1Class = package.getName();
            std::string defineName = DogGE::Utility::StringUtility::toUppercase(
                DogGE::Utility::StringUtility::toSnakeCase(f1Class));
            std::vector<Fields> fields = package.getFields();

            kainjow::mustache::mustache headerTemplate(headerFile); 
            kainjow::mustache::mustache bodyTemplate(bodyFile); 

            kainjow::mustache::data headerData;
            kainjow::mustache::data bodyData;

            std::string namespaceStr = "F1_";
            namespaceStr += this->mGame;

            std::string properties = "";
            std::string getterPrototype = "";
            std::string getterFunction = "";
            std::string setterPrototype = "";
            std::string setterFunction = "";
            for(auto field: fields){
                std::string dataType;
                if(field.getType().compare("int") == 0){
                    switch(field.getSize()){
                        case 1: {
                            properties += "uint8_t";
                            dataType = "uint8_t";
                            break;
                        }
                        case 2:{
                            properties += "uint16_t";
                            dataType = "uint16_t";
                            break;
                        }
                        case 4:{
                            properties += "uint32_t";
                            dataType = "uint32_t";
                            break;
                        }
                        case 8:{
                            properties += "uint64_t";
                            dataType = "uint64_t";
                            break;
                        }
                    }
                } else if(field.getType().compare("float") == 0){
                    properties += "float";
                    dataType = "float";
                } else if(field.getType().compare("array") == 0){
                    properties += field.getItemType()+"["+std::to_string(field.getSize())+"]";
                    dataType = field.getItemType()+"["+std::to_string(field.getSize())+"]";
                } else {
                    properties += field.getType();
                    dataType = "float";
                }
                properties += " ";
                properties += field.getName();
                properties += ";\n";
                getterPrototype += dataType+" "+
                "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"();\n";

                getterFunction += dataType+" "+f1Class+"::"+
                "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "(){return this->"+field.getName()+";}\n";

                setterPrototype += "void set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "("+dataType+" "+field.getName()+");\n";

                setterFunction += "void "+f1Class+"::"+
                "set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "("+dataType+" "+field.getName()+")"+
                "{this->"+field.getName()+" = "+field.getName()+";}\n";
            }

            //DEFINE_NAME
            headerData.set("DEFINE_NAME",defineName);
            headerData.set("NAMESPACE_NAME",namespaceStr);
            headerData.set("CLASS_NAME",f1Class);
            headerData.set("PROPERTIES",properties);
            headerData.set("SETTERS_DEFINITION",setterPrototype);
            headerData.set("GETTERS_DEFINITION",getterPrototype);
            std::string f1DataClassHeader = headerTemplate.render(headerData);

            std::string headerFileName = f1Class + ".cpp";

            bodyData.set("INCLUDE_HEADER",headerFileName);
            bodyData.set("NAMESPACE_NAME",namespaceStr);
            bodyData.set("GETTER_CODE",getterFunction);
            bodyData.set("SETTER_CODE",setterFunction);
            std::string f1DataClassBody = bodyTemplate.render(bodyData);
            
            srcDir += "/";
            srcDir += f1Class;
            srcDir += ".cpp";
            includeDir += "/";
            includeDir += f1Class;
            includeDir += ".h";
            this->writeFile(includeDir,f1DataClassHeader);
            this->writeFile(srcDir,f1DataClassBody);

        }
    }
}