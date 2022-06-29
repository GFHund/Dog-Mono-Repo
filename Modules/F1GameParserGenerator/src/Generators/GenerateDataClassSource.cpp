#include <Generators/GenerateDataClassSource.h>
#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateDataClassSource::generateSource(F1Spec spec,std::string outputFolder){
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> filenames;
            for(auto iter:packages){
                filenames.push_back(
                    this->generateF1DataClass(iter,outputFolder,spec.getName())
                );
            }
            return filenames;
        }
        std::string GenerateDataClassSource::generateF1DataClass(Packages package,std::string outputFolder,std::string gameName){
            std::string f1Class = package.getName();
            std::string headerFileName = "DataClass/";
            headerFileName += f1Class;
            headerFileName += ".h";
            std::string namespaceStr = "F1_";
            namespaceStr += gameName;

            std::string getterFunction = "";
            std::string setterFunction = "";
            std::vector<Fields> fields = package.getFields();
            for(auto field: fields){
                std::string dataType = this->getDataType(field);
                std::string functionDataType = this->getDataType(field,true);
                getterFunction += functionDataType+" "+f1Class+"::"+
                "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "(){return this->"+field.getName()+";}\n";

                setterFunction += "void "+f1Class+"::"+
                "set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "("+functionDataType+" "+field.getName()+")"+
                "{";
                if(this->isArray(field)){
                    setterFunction += "for(int i=0;i<"+std::to_string(field.getSize())+";i++){\nthis->"+field.getName()+"[i] = "+field.getName()+"[i];\n}\n";
                } else {
                    setterFunction += "this->"+field.getName()+" = "+field.getName()+";";
                }
                setterFunction += "}\n";
                
            }

            kainjow::mustache::data bodyData;
            bodyData.set("INCLUDE_HEADER",headerFileName);
            bodyData.set("NAMESPACE_NAME",namespaceStr);
            bodyData.set("GETTER_CODE",getterFunction);
            bodyData.set("SETTER_CODE",setterFunction);
            //std::string f1DataClassBody = bodyTemplate.render(bodyData);

            std::string bodyFile = outputFolder;
            bodyFile += "/src/DataClass/";
            bodyFile += f1Class;
            bodyFile += ".cpp";
            std::string ret = "src/DataClass/";
            ret += f1Class;
            ret += ".cpp";
            this->renderFile("template/F1DataClassTemplate.cpp",bodyFile,bodyData);
            return ret;
        }
    }
}