#ifndef __FILE_NOT_FOUND_EXCEPTION__
#define __FILE_NOT_FOUND_EXCEPTION__

#include <exception>
#include <string>
namespace DogGE{
    namespace F1GameParserGenerator{
        class FileNotFoundException:public std::exception{
            private:
            std::string mFilename;
            std::string mMessage;
            public:
            FileNotFoundException(std::string filename);
            virtual const char* what() const throw();
        };
    }
}

#endif