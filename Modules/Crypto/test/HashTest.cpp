#include <gtest/gtest.h>
#include <Hash.h>


TEST(Hash,Sha1){
    std::string text = "Franz jagt im komplett verwahrlosten Taxi quer durch Bayern";
    std::string hash = DogGE::Crypto::Hash::sha1(text);
    EXPECT_STREQ(hash.c_str(),"68ac906495480a3404beee4874ed853a037a7a8f");
}
/*
TEST(Hast,Sha1_2){
    std::string text = "Hallo";
    std::string hash = DogGE::Crypto::Hash::sha1(text);
    EXPECT_STREQ(hash.c_str(),"59d9a6df06b9f610f7db8e036896ed03662d168f");
}
*/