#include <gtest/gtest.h>
#include <Vector2.h>

TEST(Vector2,constructor1){
    DogGE::Math::Vector2 vec;
    EXPECT_FLOAT_EQ(vec[0],0);
    EXPECT_FLOAT_EQ(vec[1],0);
}
TEST(Vector2,constructor2){
    DogGE::Math::Vector2 vec(3,4);
    EXPECT_FLOAT_EQ(vec[0],3);
    EXPECT_FLOAT_EQ(vec[1],4);
}
TEST(Vector2,copyConstructor){
    DogGE::Math::Vector2 vec(3,4);
    DogGE::Math::Vector2 vec2(vec);
    EXPECT_FLOAT_EQ(vec2[0],3);
    EXPECT_FLOAT_EQ(vec2[1],4);
}
TEST(Vector2,setGetX){
    DogGE::Math::Vector2 vec(3,4);
    vec.setX(20);
    EXPECT_FLOAT_EQ(vec.getX(),20);
}
TEST(Vector2,setGetY){
    DogGE::Math::Vector2 vec(3,4);
    vec.setY(20);
    EXPECT_FLOAT_EQ(vec.getY(),20);
}