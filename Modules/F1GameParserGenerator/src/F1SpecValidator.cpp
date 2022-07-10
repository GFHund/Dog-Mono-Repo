#include <F1SpecValidator.h>

#include <Exceptions/PackageNotFoundException.h>
#include <iostream>

namespace DogGE{
    namespace F1GameParserGenerator{
        bool F1SpecValidator::validateSpecification(F1Spec spec){
            
            std::vector<Packages> packages = spec.getPackages();
            std::vector<std::string> errors;
            for(auto package: packages){
                int size = 0;
                std::vector<Fields> fields = package.getFields();
                for(auto field: fields){
                    try{
                        size += getSize(spec,field);
                    }catch(PackageNotFoundException e){
                        errors.push_back(field.getName() + " has a not existing type name. Type:"+e.getPackageName());
                    }
                }
                if(size != package.getSize()){
                    errors.push_back(package.getName() + " has wrong size. Expected: "+ std::to_string(size) + " gotten "+std::to_string(package.getSize()));
                }
            }
            if(errors.size() > 0){
                std::cout << "Got " << errors.size() << " Errors"<<std::endl;
                int i = 1;
                for(auto iter: errors){
                    std::cout << i << ": " << iter << std::endl;
                    i++;
                }
                return false;
            }
            return true;
        }
        bool F1SpecValidator::isStandardType(std::string type){
            if(type.compare("uint") == 0 || 
            type.compare("int") == 0 || 
            type.compare("float") == 0 || 
            type.compare("double") == 0 || 
            type.compare("char") == 0){
                return true;
            }
            return false;
        }
        int F1SpecValidator::getSize(F1Spec spec,Fields field){
            if(isStandardType(field.getType())){
                return field.getSize();
            } else if(field.getType().compare("array") == 0){ 
                if(isStandardType(field.getItemType())){
                    return field.getItemTypeSize() * field.getSize();
                } else {
                    Packages package = spec.getPackage(field.getItemType());
                    return package.getSize() * field.getSize();
                }
            } else {
                Packages package = spec.getPackage(field.getType());
                return package.getSize();
            }
        }
    }
}