#include <gtest/gtest.h>
#include <Database.h>
#include <DatabaseBuilder.h>
#include "./Entity/TestEntity.h"

TEST(Database,getType1){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromFile("test.sqlite3");
    EXPECT_EQ(data->getType(),DogGE::Database::Database::DATABASE_FILE);
    delete data;
}
TEST(Database,getType2){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromMemory();
    EXPECT_EQ(data->getType(),DogGE::Database::Database::DATABASE_IN_MEMORY);
    delete data;
}
TEST(Database,createAndCheckTable){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromMemory();
    TestEntity* entity = new TestEntity();
    entity->setNumber(500);
    entity->setReal(3.14159f);
    entity->setString("This is a Test");
    char* raw = new char[5];
    for(int i=0;i<5;i++){
        raw[i] = i;
    }
    entity->setRaw(raw,5);
    EXPECT_NO_THROW({data->persistData(entity);});
    EXPECT_TRUE(data->hasTable(entity->getTableName()));
    EXPECT_FALSE(data->hasTable("blabla"));
    delete entity;
    delete data;
}
TEST(Database,count){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromMemory();
    TestEntity* entity = new TestEntity();
    entity->setNumber(500);
    entity->setReal(3.14159f);
    entity->setString("This is a Test");
    char* raw = new char[5];
    for(int i=0;i<5;i++){
        raw[i] = i;
    }
    entity->setRaw(raw,5);
    EXPECT_NO_THROW({data->persistData(entity);});
    DogGE::Database::QueryBuilder query = data->createQueryBuilder(entity->getTableName());
    query.where("id = @id")->addIntParameter(1,1);
    int count = data->countData(query);
    EXPECT_EQ(count,1);
    delete entity;
    delete data;
}
TEST(Database,selectAll){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromMemory();
    TestEntity* entity = new TestEntity();
    entity->setNumber(500);
    entity->setReal(3.14159f);
    entity->setString("This is a Test");
    char* raw = new char[5];
    for(int i=0;i<5;i++){
        raw[i] = i;
    }
    entity->setRaw(raw,5);
    EXPECT_NO_THROW({data->persistData(entity);});
    DogGE::Database::QueryBuilder query = data->createQueryBuilder(entity->getTableName());
    query.where("id = @id")->addIntParameter(1,1);
    std::vector<TestEntity*> selectResult = data->selectAllData<TestEntity>(query);
    EXPECT_EQ(selectResult.size(),1);
    EXPECT_EQ(selectResult[0]->getId(),1);
    EXPECT_EQ(selectResult[0]->getNumber(),500);
    EXPECT_FLOAT_EQ(selectResult[0]->getReal(),3.14159f);
    EXPECT_STREQ(selectResult[0]->getString().c_str(),"This is a Test");

    for(auto iter: selectResult){
        delete iter;
    }
    delete entity;
    delete data;
}
TEST(Database,select){
    DogGE::Database::Database* data = DogGE::Database::DatabaseBuilder::fromMemory();
    TestEntity* entity = new TestEntity();
    entity->setNumber(500);
    entity->setReal(3.14159f);
    entity->setString("This is a Test");
    char* raw = new char[5];
    for(int i=0;i<5;i++){
        raw[i] = i;
    }
    entity->setRaw(raw,5);
    EXPECT_NO_THROW({data->persistData(entity);});
    DogGE::Database::QueryBuilder query = data->createQueryBuilder(entity->getTableName());
    query.where("id = @id")->addIntParameter(1,1);
    DogGE::Database::Database::ResultIterator<TestEntity> selectResult = data->selectData<TestEntity>(query);
    EXPECT_FALSE(selectResult.isError());
    EXPECT_FALSE(selectResult.isEnd());
    EXPECT_EQ(selectResult->getId(),1);
    EXPECT_EQ(selectResult->getNumber(),500);
    EXPECT_FLOAT_EQ(selectResult->getReal(),3.14159f);
    EXPECT_STREQ(selectResult->getString().c_str(),"This is a Test");
    delete entity;
    delete data;

}