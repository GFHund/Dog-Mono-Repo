#ifndef __TABLE__
#define __TABLE__
#include <string>
#include <vector>
namespace DogGE{
    namespace Database{
        class Table{
            public:
            enum DataType{
                DATATYPE_INT,
                DATATYPE_REAL,
                DATATYPE_STRING,
                DATATYPE_RAW,
                DATATYPE_INT64
            };
            std::string tableName;
            std::vector<std::pair<std::string,DataType>> columns;
        };
    }
}

#endif