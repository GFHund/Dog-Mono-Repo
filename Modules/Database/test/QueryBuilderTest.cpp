#include <gtest/gtest.h>
#include <QueryBuilder.h>
#include <Table.h>

TEST(QueryBuilder,buildCountQuery){
    std::vector<std::pair<std::string,DogGE::Database::Table::DataType>> columns;
    columns.push_back(std::pair<std::string,DogGE::Database::Table::DataType>("col_test",DogGE::Database::Table::DataType::DATATYPE_INT));

    DogGE::Database::Table table;
    table.tableName = "test";
    table.columns = columns;
    DogGE::Database::QueryBuilder builder(table);
    builder.where("col_test = @colTest");
    EXPECT_STREQ(builder.buildCountSql().c_str(),"SELECT COUNT(*) FROM test WHERE col_test = @colTest");
}
TEST(QueryBuilder,buildSql){
    std::vector<std::pair<std::string,DogGE::Database::Table::DataType>> columns;
    columns.push_back(std::pair<std::string,DogGE::Database::Table::DataType>("id",DogGE::Database::Table::DataType::DATATYPE_INT));
    columns.push_back(std::pair<std::string,DogGE::Database::Table::DataType>("col_test",DogGE::Database::Table::DataType::DATATYPE_INT));

    DogGE::Database::Table table;
    table.tableName = "test";
    table.columns = columns;
    DogGE::Database::QueryBuilder builder(table);
    builder.where("col_test = @colTest");
    EXPECT_STREQ(builder.buildSql().c_str(),"SELECT id,col_test FROM test WHERE col_test = @colTest");
}