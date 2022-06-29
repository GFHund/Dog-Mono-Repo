#include <Generators/GenerateRecorderHeader.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateRecorderHeader::generateSource(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string fileName = "Recorder_";
            fileName += spec.getName();

            kainjow::mustache::data bodyData;
            bodyData.set("NAMESPACE_NAME",namespaceStr);
            bodyData.set("CLASS_NAME",fileName);
            std::string headerFile = outputFolder;
            headerFile += "/include/";
            headerFile += "Recorder_";
            headerFile += spec.getName();
            headerFile += ".h";
            this->renderFile("template/RecorderTemplate.h",headerFile,bodyData);
            return std::vector<std::string>();
        }
    }
}