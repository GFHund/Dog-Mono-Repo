#include <gtest/gtest.h>
#include <JsonParser.h>
#include <ValueType.h>
#include <PropertyType.h>
#include <array>


TEST(ParseJson,simpleArrayType){
    std::string json = "[1,2,3]";
    std::array<int,3> compare = {1,2,3};
    DogGE::Json::JsonParser parser;
    DogGE::Tree::ArrayTree<DogGE::Json::AbstractType*> parsed = parser.parse(json);
    EXPECT_TRUE(parsed.getNodeData(1)->isArrayType());
    EXPECT_FALSE(parsed.getNodeData(1)->isObjectType());
    EXPECT_FALSE(parsed.getNodeData(1)->isPropertyType());
    EXPECT_FALSE(parsed.getNodeData(1)->isValueType());
    std::vector<DogGE::Json::AbstractType*> children = parsed.getChildren(1);
    int i=0;
    for(auto child:children){
        EXPECT_FALSE(child->isArrayType());
        EXPECT_FALSE(child->isObjectType());
        EXPECT_FALSE(child->isPropertyType());
        EXPECT_TRUE(child->isValueType());
        DogGE::Json::ValueType* valueType = (DogGE::Json::ValueType*)child;
        EXPECT_TRUE(valueType->getType() == DogGE::Json::ValueType::TYPE_INT);
        EXPECT_EQ(valueType->parseToInt(),compare[i]);
        i++;
    }
}
TEST(ParseJson,simpleObjectType){
    std::string json = "{\"a\":1,\"b\":2,\"c\":3}";
    std::array<int,3> compare = {1,2,3};
    std::array<std::string,3> propertieName = {"a","b","c"};
    DogGE::Json::JsonParser parser;
    DogGE::Tree::ArrayTree<DogGE::Json::AbstractType*> parsed = parser.parse(json);
    EXPECT_FALSE(parsed.getNodeData(1)->isArrayType());
    EXPECT_TRUE(parsed.getNodeData(1)->isObjectType());
    EXPECT_FALSE(parsed.getNodeData(1)->isPropertyType());
    EXPECT_FALSE(parsed.getNodeData(1)->isValueType());
    std::vector<DogGE::Json::AbstractType*> children = parsed.getChildren(1);
    int i=0;
    for(auto child:children){
        EXPECT_FALSE(child->isArrayType());
        EXPECT_FALSE(child->isObjectType());
        EXPECT_TRUE(child->isPropertyType());
        EXPECT_FALSE(child->isValueType());
        DogGE::Json::PropertyType* propertyType = (DogGE::Json::PropertyType*)child;
        EXPECT_STREQ(propertyType->getName().c_str(),propertieName[i].c_str());
        i++;
    }
}