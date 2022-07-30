#include <DatabaseBuilder.h>
#include "../vendor/sqlite3/sqlite3.h"
#include <Exceptions/DatabaseNotFoundException.h>
#include <Exceptions/ConvertErrorException.h>
namespace DogGE{
    namespace Database{
        Database* DatabaseBuilder::fromFile(std::string file){
            sqlite3* output;
            int rc = sqlite3_open(file.c_str(),&output);
            if(rc){
                throw DatabaseNotFoundException(file);
            }
            return new Database(output,Database::DatabaseType::DATABASE_FILE);
        }
        Database* DatabaseBuilder::fromMemory(){
            sqlite3* output;
            int rc = sqlite3_open(":memory:",&output);
            if(rc){
                throw DatabaseNotFoundException("in Memory");
            }
            return new Database(output,Database::DatabaseType::DATABASE_IN_MEMORY);
        }
        Database* DatabaseBuilder::convertFileIntoMemory(Database* db){
            Database* inMemory = DatabaseBuilder::fromMemory();
            sqlite3_backup* backup;
            backup = sqlite3_backup_init(inMemory->getRawDatabase(),"main",db->getRawDatabase(),"main");
            if(backup){
                (void) sqlite3_backup_step(backup,-1);
                (void) sqlite3_backup_finish(backup);
                return inMemory;
            } else {
                int rc = sqlite3_errcode(inMemory->getRawDatabase());
                if(rc != SQLITE_DONE){
                    throw ConvertErrorException(std::string(sqlite3_errmsg(inMemory->getRawDatabase())));
                }
            }
            return inMemory;
        }
        Database* DatabaseBuilder::convertMemoryIntoFile(Database* db,std::string file){
            Database* fileDB = DatabaseBuilder::fromFile(file);
            sqlite3_backup* backup;
            backup = sqlite3_backup_init(
                fileDB->getRawDatabase(),"main",
                db->getRawDatabase(),"main");
            if(backup){
                (void) sqlite3_backup_step(backup,-1);
                (void) sqlite3_backup_finish(backup);
                return fileDB;
            } else {
                int rc = sqlite3_errcode(fileDB->getRawDatabase());
                if(rc != SQLITE_DONE){
                    throw ConvertErrorException(std::string(sqlite3_errmsg(fileDB->getRawDatabase())));
                }
            }
            return fileDB;
        }
    }
}