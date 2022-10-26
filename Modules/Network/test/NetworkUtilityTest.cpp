#include <gtest/gtest.h>
#include <NetworkUtility.h>

TEST(NetworkUtlity,stringBase64_1){
    std::string test = "Hallo Welt";
    std::string expectedResult = "SGFsbG8gV2VsdA==";
    std::string result = DogGE::Network::NetworkUtility::encodeStringToBase64(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(NetworkUtlity,stringBase64_2){
    std::string test = "Hallo Welt1";
    std::string expectedResult = "SGFsbG8gV2VsdDE=";
    std::string result = DogGE::Network::NetworkUtility::encodeStringToBase64(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(NetworkUtlity,stringBase64_3){
    std::string test = "Hallo Welt12";
    std::string expectedResult = "SGFsbG8gV2VsdDEy";
    std::string result = DogGE::Network::NetworkUtility::encodeStringToBase64(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}
TEST(NetworkUtlity,binaryBase64_1){
    std::array<unsigned char,20> arr = {0xb3,0x7a,0x4f,0x2c,0xc0,
                                        0x62,0x4f,0x16,0x90,0xf6,
                                        0x46,0x06,0xcf,0x38,0x59,
                                        0x45,0xb2,0xbe,0xc4,0xea};
    std::string expectedResult = "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=";
    std::string result = DogGE::Network::NetworkUtility::encodeDataToBase64<20>(arr);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
    /*
    b37a4f2cc0624f1690f64606cf385945b2bec4ea
    */
}
TEST(NetworkUtlity,binaryBase64_2){
    std::array<unsigned char,19> arr = {0xb3,0x7a,0x4f,0x2c,0xc0,
                                        0x62,0x4f,0x16,0x90,0xf6,
                                        0x46,0x06,0xcf,0x38,0x59,
                                        0x45,0xb2,0xbe,0xc4};
    std::string expectedResult = "s3pPLMBiTxaQ9kYGzzhZRbK+xA==";
    std::string result = DogGE::Network::NetworkUtility::encodeDataToBase64<19>(arr);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
    /*
    b37a4f2cc0624f1690f64606cf385945b2bec4ea
    */
}
TEST(NetworkUtlity,binaryBase64_3){
    std::array<unsigned char,18> arr = {0xb3,0x7a,0x4f,0x2c,0xc0,
                                        0x62,0x4f,0x16,0x90,0xf6,
                                        0x46,0x06,0xcf,0x38,0x59,
                                        0x45,0xb2,0xbe};
    std::string expectedResult = "s3pPLMBiTxaQ9kYGzzhZRbK+";
    std::string result = DogGE::Network::NetworkUtility::encodeDataToBase64<18>(arr);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
    /*
    b37a4f2cc0624f1690f64606cf385945b2bec4ea
    */
}