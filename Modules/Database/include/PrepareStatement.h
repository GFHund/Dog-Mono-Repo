#ifndef __PREPARE_STATEMENT__
#define __PREPARE_STATEMENT__

#include "../vendor/sqlite3/sqlite3.h"
#include <stdint.h>
#include <string>
#include <string.h>
#include <array>

namespace DogGE{
    namespace Database{
        class PrepareStatement{
            private:
            sqlite3_stmt* mStmt;
            public:
            PrepareStatement(sqlite3_stmt* stmt);
            ~PrepareStatement();
            void setIntParam(int colpos,int value);
            void setInt64Param(int colpos,int64_t value);
            void setFloatParam(int colpos,float value);
            void setBlobParam(int colpos,char* data,int size);
            void resetParam();
            void execute();
            bool fetch();
            int readIntValue(unsigned int column);
            int64_t readInt64Value(unsigned int column);
            float readFloatValue(unsigned int column);
            std::string readStringValue(unsigned int column);
            template <std::size_t T>
            std::array<char,T> readBlob(unsigned int column,int* size);
        };
        template <std::size_t T>
        std::array<char,T> PrepareStatement::readBlob(unsigned int column,int* size){
            std::array<char,T> ret;
            int readSize = sqlite3_column_bytes(this->mStmt,column);
            const char* blobValue = (const char*)sqlite3_column_blob(this->mStmt,column);
            *size = readSize;
            if(T >= readSize){
                memcpy(ret.data(),blobValue,readSize);
            } else {
                memcpy(ret.data(),blobValue,T);
            }
            return ret;
        }
    }
}

#endif