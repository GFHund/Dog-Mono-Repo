#include <gtest/gtest.h>
#include <DatabaseBuilder.h>

TEST(DatabaseBuilder,FromFile){
    EXPECT_NO_THROW({DogGE::Database::DatabaseBuilder::fromFile("test.sqlite3");});
}
TEST(DatabaseBuilder,FromMemory){
    EXPECT_NO_THROW({DogGE::Database::DatabaseBuilder::fromMemory();});
}