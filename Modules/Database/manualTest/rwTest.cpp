#include <Database.h>
#include <DatabaseBuilder.h>
#include "../test/Entity/TestEntity.h"

int main(){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromFile("rwTest.sqlite3");
    TestEntity* entity = new TestEntity();
    entity->setNumber(500);
    entity->setReal(3.14159f);
    entity->setString("This is a Test");
    char* raw = new char[5];
    for(int i=0;i<5;i++){
        raw[i] = i;
    }
    entity->setRaw(raw,5);
    data->persistData(entity);
    delete entity;
    delete data;
    return 0;
}