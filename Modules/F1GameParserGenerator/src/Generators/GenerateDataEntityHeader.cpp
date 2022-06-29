#include <Generators/GenerateDataEntityHeader.h>
#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        void GenerateDataEntityHeader::generateRecordEntity(F1Spec spec,std::string outputFolder){
            kainjow::mustache::data headerData;
            std::string headerPackageName = spec.getHeaderName();
            Packages package = spec.getPackage(headerPackageName);
            std::vector<Fields> fields = package.getFields();

            std::string fileName = "F1DataEntity_";
            fileName += spec.getName();
            std::string headerFile = fileName + ".h";

            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();

            std::string f1ClassName = "F1DataEntity";

            std::string properties = "";
            std::string constructorPrototype = "";
            std::string getterPrototype = "";
            std::string setterPrototype = "";
            
            for(auto field:fields){
                std::string dataType = this->getDataType(field);
                std::string functionDataType = this->getDataType(field,true);
                properties += dataType;
                properties += " ";
                properties += field.getName();
                properties += this->getPostFixVariable(field);
                properties += ";\n";
                getterPrototype += functionDataType+" "+
                    "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"();\n";
                setterPrototype += "void set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                    "("+functionDataType+" "+field.getName()+");\n";
            }

            properties += "char* packetData;\nint packetSize;\n";
            constructorPrototype += f1ClassName+"();\n"+f1ClassName+"(char* rawData,int size);\n";
            getterPrototype += "char* getPacketData();\nint getPacketSize();";
            setterPrototype += "void setPacketData(char* packet,int size);\n";

            headerData.set("DEFINE_NAME","__F1_DATA_ENTITY__");
            headerData.set("NAMESPACE_NAME",namespaceStr);
            headerData.set("INCLUDE_FILES","");
            headerData.set("CLASS_NAME",f1ClassName);
            headerData.set("PROPERTIES",properties);
            headerData.set("CONSTRUCTORS",constructorPrototype);
            headerData.set("SETTERS_DEFINITION",setterPrototype);
            headerData.set("GETTERS_DEFINITION",getterPrototype);

            std::string absoluteHeaderFile = outputFolder;
            absoluteHeaderFile += "/include/";
            absoluteHeaderFile += headerFile;
            this->renderFile("template/F1DataEntityTemplate.h",absoluteHeaderFile,headerData);
        }

        void GenerateDataEntityHeader::generatePackagesEntity(F1Spec spec,std::string outputFolder){
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> ret;
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            for(auto package: packages){
                std::string fileName = package.getName();
                fileName += "Entity";
                std::string headerFile = fileName + ".h";

                kainjow::mustache::data headerData;

                std::string f1ClassName = package.getName();
                f1ClassName += "Entity";

                std::vector<Fields> fields = package.getFields();

                std::string properties = "";
                std::string constructorPrototype = "";
                std::string getterPrototype = "";
                std::string setterPrototype = "";

                for(auto field:fields){
                    std::string dataType = this->getDataType(field);
                    std::string functionDataType = this->getDataType(field,true);
                    properties += dataType;
                    properties += " ";
                    properties += field.getName();
                    properties += this->getPostFixVariable(field);
                    properties += ";\n";
                    getterPrototype += functionDataType+" "+
                        "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"();\n";
                    setterPrototype += "void set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                        "("+functionDataType+" "+field.getName()+");\n";
                }

                headerData.set("DEFINE_NAME","__F1_DATA_ENTITY__");
                headerData.set("NAMESPACE_NAME",namespaceStr);
                headerData.set("INCLUDE_FILES","");
                headerData.set("CLASS_NAME",f1ClassName);
                headerData.set("PROPERTIES",properties);
                headerData.set("CONSTRUCTORS",constructorPrototype);
                headerData.set("SETTERS_DEFINITION",setterPrototype);
                headerData.set("GETTERS_DEFINITION",getterPrototype);
                std::string absoluteHeaderFile = outputFolder;
                absoluteHeaderFile += "/include/Entity/";
                absoluteHeaderFile += headerFile;
                this->renderFile("template/F1DataEntityTemplate.h",absoluteHeaderFile,headerData);
            }

            
        }

        std::vector<std::string> GenerateDataEntityHeader::generateSource(F1Spec spec,std::string outputFolder){
            this->generatePackagesEntity(spec,outputFolder);
            this->generateRecordEntity(spec,outputFolder);
            return std::vector<std::string>();
        }
    }
}