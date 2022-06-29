#ifndef __DATA_TYPE_NOT_FOUND_EXCEPTION__
#define __DATA_TYPE_NOT_FOUND_EXCEPTION__
#pragma once

#include <exception>
#include <string>
namespace DogGE{
    namespace F1GameParserGenerator{
        class DataTypeNotFoundException:public std::exception{
            private:
            std::string mDataType;
            int mDataTypeSize;
            std::string mMessage;
            public:
            DataTypeNotFoundException(std::string dataType,int size);
            virtual const char* what() const throw();
        };
    }
}

#endif