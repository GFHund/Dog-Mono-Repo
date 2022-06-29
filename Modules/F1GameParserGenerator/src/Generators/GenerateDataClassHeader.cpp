#include <Generators/GenerateDataClassHeader.h>
#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::vector<std::string> GenerateDataClassHeader::generateSource(F1Spec spec,std::string outputFolder){
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> filenames;
            for(auto iter:packages){
                this->generateF1DataClass(iter,outputFolder,spec.getName());
            }
            return filenames;
        }
        void GenerateDataClassHeader::generateF1DataClass(Packages package,std::string outputFolder,std::string gameName){
            std::string f1Class = package.getName();
            std::string defineName = DogGE::Utility::StringUtility::toUppercase(
                DogGE::Utility::StringUtility::toSnakeCase(f1Class));
            std::string namespaceStr = "F1_";
            namespaceStr += gameName;
            std::string includes = "";
            
            std::string properties = "";
            std::string getterPrototype = "";
            std::string setterPrototype = "";
            std::vector<Fields> fields = package.getFields();
            for(auto field: fields){
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
                if(this->isClass(field)){
                    if(this->isArray(field)){
                        includes += "#include <DataClass/"+field.getItemType()+".h>\n";
                    } else {
                        includes += "#include <DataClass/"+field.getType()+".h>\n";
                    }
                }
                
            }
            
            kainjow::mustache::data headerData;
            headerData.set("DEFINE_NAME",defineName);
            headerData.set("NAMESPACE_NAME",namespaceStr);
            headerData.set("INCLUDE_FILES",includes);
            headerData.set("CLASS_NAME",f1Class);
            headerData.set("PROPERTIES",properties);
            headerData.set("SETTERS_DEFINITION",setterPrototype);
            headerData.set("GETTERS_DEFINITION",getterPrototype);
            //std::string f1DataClassHeader = headerTemplate.render(headerData);
            std::string headerFile = outputFolder;
            
            headerFile += "/include/DataClass/";
            headerFile += f1Class;
            headerFile += ".h";
            this->renderFile("template/F1DataClassTemplate.h",headerFile,headerData);
            

        }
    }
}