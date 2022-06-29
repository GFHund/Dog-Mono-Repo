#include <F1Spec.h>

#include <Exceptions/PackageNotFoundException.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        void F1Spec::setName(std::string name){
            this->mName = name;
        }
        std::string F1Spec::getName(){
            return this->mName;
        }
        void F1Spec::addPackage(Packages package){
            this->mPackages.push_back(package);
        }

        std::vector<Packages> F1Spec::getPackages(){
            return this->mPackages;
        }
        Packages F1Spec::getPackage(std::string packageName){
            for(auto iter: this->mPackages){
                if(packageName.compare(iter.getName().c_str()) == 0){
                    return iter;
                }
            }
            throw PackageNotFoundException(packageName);
        }

        void F1Spec::setHeaderName(std::string headerName){
            this->mHeaderName = headerName;
        }
        std::string F1Spec::getHeaderName(){
            return this->mHeaderName;
        }

        void F1Spec::addPackagesMapping(int id,std::string packageName){
            this->mPackagesMapping.insert(this->mPackagesMapping.end(),std::pair<int,std::string>(id,packageName));
        }
        std::map<int,std::string> F1Spec::getPackagesMapping(){
            return this->mPackagesMapping;
        }
    }
}