#include <Generators/GenerateRecorderSource.h>
#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateRecorderSource::generateSource(F1Spec spec,std::string outputFolder){
            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string fileName = "Recorder_";
            fileName += spec.getName();
            std::string includeFile = fileName + ".h";
            std::string sourceFile = fileName + ".cpp";
            std::string entityClassName = "F1DataEntity";
            //entityClassName += spec.getName();
            std::string entityHeaderFileInclude = "#include <F1DataEntity_";
            entityHeaderFileInclude += spec.getName();
            entityHeaderFileInclude += ".h>";
            std::string headerPackageName = spec.getHeaderName();
            Packages headerPackage = spec.getPackage(headerPackageName);
            std::vector<Fields> fields = headerPackage.getFields();
            std::string tableName = "F1DataEntity";
            std::string tableFieldNames = "";
            std::string tableFieldValues = "";
            std::string fillInsertStmt = "";
            bool bFirst = true;
            int i = 1;

            for(auto field:fields){
                if(bFirst){
                    bFirst = false;
                } else {
                    tableFieldNames += ",";
                    tableFieldValues += ",";
                }
                tableFieldNames += "`"+field.getName()+"`";
                tableFieldValues += "@"+field.getName();
                if(field.getType().compare("int") == 0 || field.getType().compare("uint") == 0){
                    if(field.getSize() > 4){
                        fillInsertStmt += "insertStatement->setInt64Param("+
                        std::to_string(i)+
                        ",entity.get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                        "());\n";
                    } else {
                        fillInsertStmt += "insertStatement->setIntParam("+
                        std::to_string(i)+
                        ",entity.get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                        "());\n";
                    }
                } else if(field.getType().compare("float") == 0){
                    fillInsertStmt += "insertStatement->setFloatParam("+
                        std::to_string(i)+
                        ",entity.get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                        "());\n";
                }
                
                i++;
            }
            tableFieldNames += ",`packet`";
            tableFieldValues += ",@packet";
            fillInsertStmt += "insertStatement->setBlobParam("+std::to_string(i)+",entity.getPacketData(),entity.getPacketSize());\n";

            kainjow::mustache::data bodyData;
            bodyData.set("NAMESPACE_NAME",namespaceStr);
            bodyData.set("CLASS_NAME",fileName);
            bodyData.set("HEADER_FILE",includeFile);
            bodyData.set("ENTITY_FILE_NAME",entityClassName);
            bodyData.set("ADDITIONAL_INCLUDES",entityHeaderFileInclude);
            bodyData.set("TABLE_NAME",tableName);
            bodyData.set("TABLE_FIELD_NAMES",tableFieldNames);
            bodyData.set("TABLE_FIELD_VALUES",tableFieldValues);
            bodyData.set("FILL_INSERT_STMT",fillInsertStmt);

            std::vector<std::string> ret;
            std::string cMakeFile = "src/";
            cMakeFile += sourceFile;
            ret.push_back(cMakeFile);
            
            std::string bodyFile = outputFolder;
            bodyFile += "/src/";
            bodyFile += sourceFile;
            this->renderFile("template/RecorderTemplate.cpp",bodyFile,bodyData);
            return ret;
        }
    }
}