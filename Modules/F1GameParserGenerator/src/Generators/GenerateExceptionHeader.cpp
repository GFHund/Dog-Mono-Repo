#include <Generators/GenerateExceptionHeader.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateExceptionHeader::generateSource(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();

            std::string fileName = "ValidationException";

            std::string includes = "#include <string>";
            std::string properties = "std::string message;";

            kainjow::mustache::data headData;
            headData.set("INCLUDES",includes);
            headData.set("NAMESPACE_NAME",namespaceStr);
            headData.set("CLASS_NAME",fileName);
            headData.set("PROPERTIES",properties);
            headData.set("CONSTRUCTOR_ARGS","");
            headData.set("GETTER_FUNCTION","");

            std::string headerFile = outputFolder;
            headerFile += "/include/Exceptions/";
            headerFile += fileName;
            headerFile += ".h";
            this->renderFile("template/ExceptionTemplate.h",headerFile,headData);
            return std::vector<std::string>();
        }
    }
}