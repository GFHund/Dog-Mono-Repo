#include <gtest/gtest.h>
#include <F1SpecBuilder.h>

TEST(F1SpecBuilderTest,read){
    DogGE::F1GameParserGenerator::F1Spec spec = DogGE::F1GameParserGenerator::F1SpecBuilder::build("2021");
    EXPECT_STREQ(spec.getName().c_str(),"F1Game2021");
    EXPECT_EQ(spec.getPackages().size(),13);
}