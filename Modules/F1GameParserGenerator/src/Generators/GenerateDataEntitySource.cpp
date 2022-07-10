#include <Generators/GenerateDataEntitySource.h>

#include <StringUtility.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        std::string GenerateDataEntitySource::generateRecordEntity(F1Spec spec,std::string outputFolder){
            kainjow::mustache::data sourceData;
            std::string headerPackageName = spec.getHeaderName();
            Packages package = spec.getPackage(headerPackageName);
            std::vector<Fields> fields = package.getFields();
            std::string fileName = "F1DataEntity_";
            fileName += spec.getName();
            std::string headerFile = fileName + ".h";
            std::string sourceFile = fileName + ".cpp";

            std::string f1Class = "F1DataEntity";

            std::string namespaceStr = "F1_";
            namespaceStr += spec.getName();
            std::string includeFiles = "#include <Exceptions/ValidationException.h>\n";

            std::string constructorFunction = "";
            std::string getterFunction = "";
            std::string setterFunction = "";
            std::string tableFields = "";
            std::string matchIntData = "";
            std::string matchInt64Data = "";
            std::string matchRealData = "";
            std::string matchRawData = "";
            std::string getIntMap = "";
            std::string getInt64Map = "";
            std::string getRealMap = "";
            std::string getRawMap = "";

            constructorFunction += f1Class+"::"+f1Class+"(){}\n"+f1Class+"::"+f1Class+"(char* rawData,int size){\n";
            int offset = 0;
            for(auto field:fields){
                std::string dataType = this->getDataType(field);
                std::string functionDataType = this->getDataType(field,true);
                getterFunction += functionDataType+" "+f1Class+"::"+
                "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "(){return this->"+field.getName()+";}\n";

                setterFunction += "void "+f1Class+"::"+
                "set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                "("+functionDataType+" "+field.getName()+")"+
                "{this->"+field.getName()+" = "+field.getName()+";}\n";

                std::string dbDataType = this->getDatabaseType(field);
                tableFields += ",`"+field.getName()+"` "+dbDataType;

                
                constructorFunction += "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(*(("+dataType+"*)(rawData+" + std::to_string(offset) + ")));\n";
                //Condition for validation should be in the spec file but at first i write this it as a constant
                if(field.getName().compare("packetFormat") == 0){
                    constructorFunction += "if(this->getPacketFormat() != "+spec.getName()+"){throw ValidationException();}\n";
                }
                offset += field.getSize();

                if(field.getType().compare("int") == 0){
                    if(field.getSize() > 4){
                        if(matchInt64Data.size() > 0){
                            matchInt64Data += " else ";
                        }
                        matchInt64Data += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                        "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                        "}";
                        getInt64Map += "ret.insert(std::pair<std::string,int64_t>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));\n";
                    } else {
                        matchIntData += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                        "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                        "} else ";
                        getIntMap += "ret.insert(std::pair<std::string,int>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));\n";
                    }
                    
                } else if(field.getType().compare("float") == 0){
                    if(matchRealData.size() > 0){
                        matchRealData += " else ";
                    } 
                    matchRealData += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                    "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                    "}";
                    getRealMap += "ret.insert(std::pair<std::string,float>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));";
                }

            }
            
            getterFunction += "char* " + f1Class + "::getPacketData(){return this->packetData;}\nint " + f1Class + "::getPacketSize(){return this->packetSize;}\n";
            setterFunction += "void " + f1Class + "::setPacketData(char* packet,int size){for(int i=0;i<size;i++){this->packetData[i] = packet[i];}this->packetSize = size;}\n";
            tableFields += ",`packet` BLOB";
            constructorFunction += "this->packetData = rawData;\nthis->packetSize = size;\n}";
            if(matchIntData.size() <= 0){
               matchIntData += "DogGE::Database::AbstractEntity::matchIntData(column,data);\n";
            } else {
                matchIntData += "{DogGE::Database::AbstractEntity::matchIntData(column,data);}\n";
            }
            matchRawData += "if(column.compare(\"packet\") == 0){this->setPacketData(data,length);}";
            getRawMap += "ret.insert( std::pair<std::string,std::pair<char*,int>>(\"packet\",std::pair<char*,int>( this->getPacketData(),this->getPacketSize() )) );";

            sourceData.set("INCLUDE_HEADER",headerFile);
            sourceData.set("INCLUDE_FILES",includeFiles);
            sourceData.set("NAMESPACE_NAME",namespaceStr);
            sourceData.set("CLASS_NAME",f1Class);
            sourceData.set("CONSTRUCTORS",constructorFunction);
            sourceData.set("GETTER_CODE",getterFunction);
            sourceData.set("SETTER_CODE",setterFunction);
            sourceData.set("TABLE_NAME",f1Class);
            sourceData.set("TABLE_FIELDS",tableFields);
            sourceData.set("MATCH_INT_DATA",matchIntData);
            sourceData.set("MATCH_INT64_DATA",matchInt64Data);
            sourceData.set("MATCH_REAL_DATA",matchRealData);
            sourceData.set("MATCH_RAW_DATA",matchRawData);
            sourceData.set("GET_INT_MAP",getIntMap);
            sourceData.set("GET_INT64_MAP",getInt64Map);
            sourceData.set("GET_REAL_MAP",getRealMap);
            sourceData.set("GET_RAW_MAP",getRawMap);

            std::string absoluteSourceFile = outputFolder;
            absoluteSourceFile += "/src/";
            absoluteSourceFile += sourceFile;
            this->renderFile("template/F1DataEntityTemplate.cpp",absoluteSourceFile,sourceData);

            std::string cMakeFile = "src/"+ sourceFile;
            //std::vector<std::string> ret;
            //ret.push_back(cMakeFile);
            //return ret;
            return cMakeFile;
        }

        std::vector<std::string> GenerateDataEntitySource::generatePackagesEntity(F1Spec spec,std::string outputFolder){
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> ret;
            for(auto package: packages){
                std::string f1Class = package.getName();
                f1Class += "Entity";
                kainjow::mustache::data sourceData;
                std::string headerFile = f1Class + ".h";
                std::string sourceFile = f1Class + ".cpp";
                std::string includeFiles = "#include <Exceptions/ValidationException.h>\n";
                std::string namespaceStr = "F1_";
                namespaceStr += spec.getName();
                std::string constructorFunction = "";
                std::string getterFunction = "";
                std::string setterFunction = "";
                std::string tableFields = "";
                std::string matchIntData = "";
                std::string matchInt64Data = "";
                std::string matchRealData = "";
                std::string matchRawData = "";
                std::string getIntMap = "";
                std::string getInt64Map = "";
                std::string getRealMap = "";
                std::string getRawMap = "";
                constructorFunction += f1Class+"::"+f1Class+"(){}\n"+f1Class+"::"+f1Class+"(char* rawData,int size,int offset){\n";

                std::vector<Fields> fields = package.getFields();
                int offset = 0;
                for(auto field: fields){
                    std::string dataType = this->getDataType(field);
                    std::string functionDataType = this->getDataType(field,true);
                    
                    if(!this->isClass(field)){
                        constructorFunction += "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(*(("+dataType+"*)(rawData+" + std::to_string(offset) + ")));\n";
                        //Condition for validation should be in the spec file but at first i write this it as a constant
                        if(field.getName().compare("packetFormat") == 0){
                            constructorFunction += "if(this->getPacketFormat() != "+spec.getName()+"){throw ValidationException();}\n";
                        }
                        offset += field.getSize();
                    } else {
                        constructorFunction += "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                            "("+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(rawData,size,"+std::to_string(offset)+"));\n";
                    }
                    
                    getterFunction += functionDataType+" "+f1Class+"::"+
                    "get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                    "(){return this->"+field.getName()+";}\n";

                    setterFunction += "void "+f1Class+"::"+
                    "set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+
                    "("+functionDataType+" "+field.getName()+")"+
                    "{this->"+field.getName()+" = "+field.getName()+";}\n";
                    

                    std::string dbDataType = this->getDatabaseType(field);
                    tableFields += ",`"+field.getName()+"` "+dbDataType;

                    if(field.getType().compare("int") == 0){
                        if(field.getSize() > 4){
                            if(matchInt64Data.size() > 0){
                                matchInt64Data += " else ";
                            }
                            matchInt64Data += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                            "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                            "}";
                            getInt64Map += "ret.insert(std::pair<std::string,int64_t>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));\n";
                        } else {
                            matchIntData += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                            "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                            "} else ";
                            getIntMap += "ret.insert(std::pair<std::string,int>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));\n";
                        }
                        
                    } else if(field.getType().compare("float") == 0){
                        if(matchRealData.size() > 0){
                            matchRealData += " else ";
                        } 
                        matchRealData += "if(column.compare(\""+field.getName()+"\") == 0){\n"
                        "this->set"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"(data);\n"
                        "}";
                        getRealMap += "ret.insert(std::pair<std::string,float>(\""+field.getName()+"\",this->get"+DogGE::Utility::StringUtility::ucfirst(field.getName())+"()));";
                    }
                }
                std::string absoluteSourceFile = outputFolder;

                sourceData.set("INCLUDE_HEADER",headerFile);
                sourceData.set("INCLUDE_FILES",includeFiles);
                sourceData.set("NAMESPACE_NAME",namespaceStr);
                sourceData.set("CLASS_NAME",f1Class);
                sourceData.set("CONSTRUCTORS",constructorFunction);
                sourceData.set("GETTER_CODE",getterFunction);
                sourceData.set("SETTER_CODE",setterFunction);
                sourceData.set("TABLE_NAME",f1Class);
                sourceData.set("TABLE_FIELDS",tableFields);
                sourceData.set("MATCH_INT_DATA",matchIntData);
                sourceData.set("MATCH_INT64_DATA",matchInt64Data);
                sourceData.set("MATCH_REAL_DATA",matchRealData);
                sourceData.set("MATCH_RAW_DATA",matchRawData);
                sourceData.set("GET_INT_MAP",getIntMap);
                sourceData.set("GET_INT64_MAP",getInt64Map);
                sourceData.set("GET_REAL_MAP",getRealMap);
                sourceData.set("GET_RAW_MAP",getRawMap);

                absoluteSourceFile += "/src/Entity/";
                absoluteSourceFile += f1Class;
                absoluteSourceFile += ".cpp";
                this->renderFile("template/F1DataEntityTemplate.cpp",absoluteSourceFile,sourceData);

                std::string retSourceFile = "src/Entity/";
                retSourceFile += f1Class;
                retSourceFile += ".cpp";
                ret.push_back(retSourceFile);
            }
            return ret;
        }

        std::vector<std::string> GenerateDataEntitySource::generateSource(F1Spec spec,std::string outputFolder){
            std::vector<std::string> ret = this->generatePackagesEntity(spec,outputFolder);
            ret.push_back(this->generateRecordEntity(spec,outputFolder));
            return ret;
        }
        std::string GenerateDataEntitySource::getDatabaseType(Fields field){
            std::string dataType;
            if(field.getType().compare("int") == 0 || field.getType().compare("uint") == 0){
                if(field.getSize() > 4){
                    dataType = "BIGINT";
                } else {
                    dataType = "INTEGER";
                }
            } else if(field.getType().compare("float") == 0){
                dataType = "REAL";
            } else if(field.getType().compare("array") == 0){
                dataType = "INTEGER";
            } else {
                dataType = "REAL";
            }
            return dataType;
        }
    }
}