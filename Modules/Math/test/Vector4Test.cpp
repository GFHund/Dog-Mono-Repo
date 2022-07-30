#include <gtest/gtest.h>
#include <Vector4.h>

TEST(Vector4,constructor1){
    DogGE::Math::Vector4 vec;
    EXPECT_FLOAT_EQ(vec[0],0);
    EXPECT_FLOAT_EQ(vec[1],0);
    EXPECT_FLOAT_EQ(vec[2],0);
    EXPECT_FLOAT_EQ(vec[3],0);
}
TEST(Vector4,constructor2){
    DogGE::Math::Vector4 vec(1,2,3,4);
    EXPECT_FLOAT_EQ(vec[0],1);
    EXPECT_FLOAT_EQ(vec[1],2);
    EXPECT_FLOAT_EQ(vec[2],3);
    EXPECT_FLOAT_EQ(vec[3],4);
}
TEST(Vector4,copyConstructor){
    DogGE::Math::Vector4 vec(1,2,3,4);
    DogGE::Math::Vector4 vec2(vec);
    EXPECT_FLOAT_EQ(vec2[0],1);
    EXPECT_FLOAT_EQ(vec2[1],2);
    EXPECT_FLOAT_EQ(vec2[2],3);
    EXPECT_FLOAT_EQ(vec2[3],4);
}
TEST(Vector4,setGetX){
    DogGE::Math::Vector4 vec(1,2,3,4);
    vec.setX(20);
    EXPECT_FLOAT_EQ(vec.getX(),20);
}
TEST(Vector4,setGetY){
    DogGE::Math::Vector4 vec(1,2,3,4);
    vec.setY(20);
    EXPECT_FLOAT_EQ(vec.getY(),20);
}
TEST(Vector4,setGetZ){
    DogGE::Math::Vector4 vec(1,2,3,4);
    vec.setZ(20);
    EXPECT_FLOAT_EQ(vec.getZ(),20);
}
TEST(Vector4,setGetW){
    DogGE::Math::Vector4 vec(1,2,3,4);
    vec.setW(20);
    EXPECT_FLOAT_EQ(vec.getW(),20);
}