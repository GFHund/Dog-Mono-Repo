#ifndef __DATABASE_BUILDER__
#define __DATABASE_BUILDER__

#include <Database.h>
#include <string>
namespace DogGE{
    namespace Database{
        class DatabaseBuilder{
            public:
            static Database* fromFile(std::string file);
            static Database* fromMemory();
            static Database* convertFileIntoMemory(Database* db);
            static Database* convertMemoryIntoFile(Database* db,std::string file);
        };
    }
}

#endif