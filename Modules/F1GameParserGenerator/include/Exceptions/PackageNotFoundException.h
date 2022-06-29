#ifndef __PACKAGE_NOT_FOUND_EXCEPTION__
#define __PACKAGE_NOT_FOUND_EXCEPTION__
#pragma once

#include <exception>
#include <string>
namespace DogGE{
    namespace F1GameParserGenerator{
        class PackageNotFoundException:public std::exception{
            private:
            std::string mPackageName;
            std::string mMessage;
            public:
            PackageNotFoundException(std::string packageName);
            virtual const char* what() const throw();
        };
    }
}

#endif