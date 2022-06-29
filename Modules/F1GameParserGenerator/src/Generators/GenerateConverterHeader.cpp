#include <Generators/GenerateConverterHeader.h>
#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateConverterHeader::generateSource(F1Spec spec,std::string outputFolder){
            std::vector<std::string> ret;
            this->generateCtConverter(spec,outputFolder);
            this->generateF1StandardFormat(spec,outputFolder);
            return ret;
        }
        void GenerateConverterHeader::generateCtConverter(F1Spec spec,std::string outputFolder){
            std::string f1Class = spec.getName();
            std::string defineName = DogGE::Utility::StringUtility::toUppercase(
                DogGE::Utility::StringUtility::toSnakeCase(f1Class));
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string className = "ConverterCTFormat";

            kainjow::mustache::data headerData;
            headerData.set("DEFINE_NAME",defineName);
            headerData.set("NAMESPACE_NAME",namespaceStr);
            headerData.set("CLASS_NAME",className);

            std::string converterHeaderFile = outputFolder;
            converterHeaderFile += "/include/F1_";
            converterHeaderFile += spec.getName();
            converterHeaderFile += "_ct_converter.h";
            this->renderFile("template/ConverterTemplate.h",converterHeaderFile,headerData);

        }
        void GenerateConverterHeader::generateF1StandardFormat(F1Spec spec,std::string outputFolder){
            std::string f1Class = spec.getName();
            std::string defineName = DogGE::Utility::StringUtility::toUppercase(
                DogGE::Utility::StringUtility::toSnakeCase(f1Class));
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string className = "ConverterStandardFormat";

            kainjow::mustache::data headerData;
            headerData.set("DEFINE_NAME",defineName);
            headerData.set("NAMESPACE_NAME",namespaceStr);
            headerData.set("CLASS_NAME",className);

            std::string converterHeaderFile = outputFolder;
            converterHeaderFile += "/include/F1_";
            converterHeaderFile += spec.getName();
            converterHeaderFile += "_f1_converter.h";
            this->renderFile("template/ConverterTemplate.h",converterHeaderFile,headerData);
        }
    }
}