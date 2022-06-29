#include <gtest/gtest.h>
#include <StringUtility.h>

TEST(StringUtility,base64EncodeTest1){
    std::string test = "Hallo Welt";
    std::string expectedResult = "SGFsbG8gV2VsdA==";
    std::string result = DogGE::Utility::StringUtility::base64Encode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,base64EncodeTest2){
    std::string test = "Hallo Welt1";
    std::string expectedResult = "SGFsbG8gV2VsdDE=";
    std::string result = DogGE::Utility::StringUtility::base64Encode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,base64EncodeTest3){
    std::string test = "Hallo Welt12";
    std::string expectedResult = "SGFsbG8gV2VsdDEy";
    std::string result = DogGE::Utility::StringUtility::base64Encode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,base64DecodeTest1){
    std::string test = "SGFsbG8gV2VsdA==";
    std::string expectedResult = "Hallo Welt";
    std::string result = DogGE::Utility::StringUtility::base64Decode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,base64DecodeTest2){
    std::string test = "SGFsbG8gV2VsdDE=";
    std::string expectedResult = "Hallo Welt1";
    std::string result = DogGE::Utility::StringUtility::base64Decode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,base64DecodeTest3){
    std::string test = "SGFsbG8gV2VsdDEy";
    std::string expectedResult = "Hallo Welt12";
    std::string result = DogGE::Utility::StringUtility::base64Decode(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,ucfirstTest1){
    std::string test = "halloWelt";
    std::string expectedResult = "HalloWelt";
    std::string result = DogGE::Utility::StringUtility::ucfirst(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,ucfirstTest2){
    std::string test = "HalloWelt";
    std::string expectedResult = "HalloWelt";
    std::string result = DogGE::Utility::StringUtility::ucfirst(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,ucfirstTest3){
    std::string test = "=HalloWelt";
    std::string expectedResult = "=HalloWelt";
    std::string result = DogGE::Utility::StringUtility::ucfirst(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toUppercaseTest){
    std::string test = "HaLlO WeLt";
    std::string expectedResult = "HALLO WELT";
    std::string result = DogGE::Utility::StringUtility::toUppercase(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toLowercaseTest){
    std::string test = "HaLlO WeLt";
    std::string expectedResult = "hallo welt";
    std::string result = DogGE::Utility::StringUtility::toLowercase(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,replaceCharTest){
    std::string test = "hallo Welt";
    std::string expectedResult = "hallo_Welt";
    std::string result = DogGE::Utility::StringUtility::replaceChar(test,' ','_');
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toSnakeCaseTest1){
    std::string test = "hallo Welt";
    std::string expectedResult = "hallo_welt";
    std::string result = DogGE::Utility::StringUtility::toSnakeCase(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toSnakeCaseTest2){
    std::string test = "hallo-Welt";
    std::string expectedResult = "hallo_welt";
    std::string result = DogGE::Utility::StringUtility::toSnakeCase(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toSnakeCaseTest3){
    std::string test = "halloWelt";
    std::string expectedResult = "hallo_welt";
    std::string result = DogGE::Utility::StringUtility::toSnakeCase(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase1){
    std::string test = "hallo welt";
    std::string expectedResult = "halloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,false);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase2){
    std::string test = "hallo welt";
    std::string expectedResult = "HalloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,true);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase3){
    std::string test = "hallo-welt";
    std::string expectedResult = "halloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,false);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase4){
    std::string test = "hallo-welt";
    std::string expectedResult = "HalloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,true);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase5){
    std::string test = "hallo_welt";
    std::string expectedResult = "halloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,false);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(StringUtility,toCamelCase6){
    std::string test = "hallo_welt";
    std::string expectedResult = "HalloWelt";
    std::string result = DogGE::Utility::StringUtility::toCamelCase(test,true);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}