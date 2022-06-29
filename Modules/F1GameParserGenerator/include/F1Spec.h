#ifndef __F1_SPEC__
#define __F1_SPEC__
#pragma once

#include <string>
#include <map>
#include <Packages.h>

namespace DogGE{
    namespace F1GameParserGenerator{
        class F1Spec{
            private:
            std::string mName;
            std::string mHeaderName;
            std::vector<Packages> mPackages;
            std::map<int,std::string> mPackagesMapping;
            public:
            void setName(std::string name);
            std::string getName();

            void addPackage(Packages package);
            std::vector<Packages> getPackages();
            Packages getPackage(std::string packageName);

            void addPackagesMapping(int id,std::string packageName);
            std::map<int,std::string> getPackagesMapping();

            void setHeaderName(std::string headerName);
            std::string getHeaderName();
        };
    }
}

#endif