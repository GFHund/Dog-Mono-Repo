#include <Generators/GenerateConverterSource.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateConverterSource::generateSource(F1Spec spec,std::string outputFolder){
            std::vector<std::string> ret;
            ret.push_back(this->generateCtConverter(spec,outputFolder));
            ret.push_back(this->generateF1StandardFormat(spec,outputFolder));
            return ret;
        }
        std::string GenerateConverterSource::generateCtConverter(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string className = "ConverterCTFormat";
            std::string headerFile = "F1_";
            headerFile += spec.getName();
            headerFile += "_ct_converter.h";
            std::string dbTable = "F1DataEntity";
            std::string entityClass = "F1DataEntity";
            std::string selectPackages = "switch(packetId){\n";

            std::map<int,std::string> packagesMapping = spec.getPackagesMapping();
            for(auto [packageID,packageName]:packagesMapping){
                Packages package = spec.getPackage(packageName);
                selectPackages += "case " + std::to_string(packageID) + ":{\n";
                selectPackages += packageName;
                selectPackages += "Entity(data.data(),";
                selectPackages += std::to_string(package.getSize());
                selectPackages += ");\n";
                selectPackages += "break;\n}\n";
            }

            kainjow::mustache::data sourceData;
            sourceData.set("HEADER_FILE",headerFile);
            sourceData.set("NAMESPACE_NAME",namespaceStr);
            sourceData.set("CLASS_NAME",className);
            sourceData.set("DB_TABLE",dbTable);
            sourceData.set("ENTITY_CLASS",entityClass);
            sourceData.set("PACKET_FORMAT",spec.getName());
            sourceData.set("SELECT_PACKAGES",selectPackages);

            std::string converterSourceFile = outputFolder;
            converterSourceFile += "/src/F1_";
            converterSourceFile += spec.getName();
            converterSourceFile += "_ct_converter.cpp";
            this->renderFile("template/ConverterTemplate.cpp",converterSourceFile,sourceData);
            std::string ret = "src/F1_";
            ret += spec.getName();
            ret += "_ct_converter.cpp";
            return ret;
        }
        std::string GenerateConverterSource::generateF1StandardFormat(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string className = "ConverterStandardFormat";
            std::string headerFile = "F1_";
            headerFile += spec.getName();
            headerFile += "_f1_converter.h";
            std::string dbTable = "F1DataEntity";
            std::string entityClass = "F1DataEntity";
            std::string selectPackages = "DogGE::Database::AbstractEntity* packageEntity;\nswitch(packetId){\n";

            std::map<int,std::string> packagesMapping = spec.getPackagesMapping();
            for(auto [packageID,packageName]:packagesMapping){
                Packages package = spec.getPackage(packageName);
                selectPackages += "case " + std::to_string(packageID) + ":{\n";
                selectPackages += "packageEntity = new ";
                selectPackages += packageName;
                selectPackages += "Entity(data.data(),";
                selectPackages += std::to_string(package.getSize());
                selectPackages += ");\n";
                selectPackages += "break;\n}\n";
            }
            selectPackages += "output->persistData(packageEntity);\n delete packageEntity;\n";

            kainjow::mustache::data sourceData;
            sourceData.set("HEADER_FILE",headerFile);
            sourceData.set("NAMESPACE_NAME",namespaceStr);
            sourceData.set("CLASS_NAME",className);
            sourceData.set("DB_TABLE",dbTable);
            sourceData.set("ENTITY_CLASS",entityClass);
            sourceData.set("PACKET_FORMAT",spec.getName());
            sourceData.set("SELECT_PACKAGES",selectPackages);

            std::string converterSourceFile = outputFolder;
            converterSourceFile += "/src/F1_";
            converterSourceFile += spec.getName();
            converterSourceFile += "_f1_converter.cpp";
            this->renderFile("template/ConverterTemplate.cpp",converterSourceFile,sourceData);
            
            std::string ret = "src/F1_";
            ret += spec.getName();
            ret += "_f1_converter.cpp";
            return ret;
        }
    }
}