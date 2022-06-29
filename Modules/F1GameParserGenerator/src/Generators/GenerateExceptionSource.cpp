#include <Generators/GenerateExceptionSource.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateExceptionSource::generateSource(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();

            std::string fileName = "ValidationException";
            std::string headerFile = "Exceptions/";
            headerFile += fileName;
            headerFile += ".h";

            kainjow::mustache::data bodyData;
            bodyData.set("EXCEPTION_HEADER",headerFile);
            bodyData.set("NAMESPACE_NAME",namespaceStr);
            bodyData.set("CLASS_NAME",fileName);
            bodyData.set("CONSTRUCTOR_ARGS","");
            bodyData.set("CONSTRUCTOR_FUNCTION","this->message = \"Validation Fehler\";");
            bodyData.set("GETTER_FUNCTION","");
            bodyData.set("RETURN_STRING","this->message.c_str();");
            
            std::string sourceFile = outputFolder;
            sourceFile += "/src/Exceptions/";
            sourceFile += fileName;
            sourceFile += ".cpp";

            std::vector<std::string> ret;
            std::string cMakeFile = "src/Exceptions/ValidationException.cpp";
            ret.push_back(cMakeFile);

            this->renderFile("template/ExceptionTemplate.cpp",sourceFile,bodyData);
            return ret;
        }
        
    }
}