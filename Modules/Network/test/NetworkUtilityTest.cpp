#include <gtest/gtest.h>
#include <NetworkUtility.h>

TEST(NetworkUtlity,stringBase64_1){
    std::string test = "Hallo Welt";
    std::string expectedResult = "SGFsbG8gV2VsdA==";
    std::string result = DogGE::Network::NetworkUtility::encodeStringToBase64(test);
    EXPECT_STREQ(result.c_str(),expectedResult.c_str());
}