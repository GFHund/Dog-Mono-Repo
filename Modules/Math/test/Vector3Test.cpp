#include <gtest/gtest.h>
#include <Vector3.h>

TEST(Vector3,constructor1){
    DogGE::Math::Vector3 vec;
    EXPECT_FLOAT_EQ(vec[0],0);
    EXPECT_FLOAT_EQ(vec[1],0);
    EXPECT_FLOAT_EQ(vec[2],0);
}
TEST(Vector3,constructor2){
    DogGE::Math::Vector3 vec(1,2,3);
    EXPECT_FLOAT_EQ(vec[0],1);
    EXPECT_FLOAT_EQ(vec[1],2);
    EXPECT_FLOAT_EQ(vec[2],3);
}
TEST(Vector3,copyConstructor){
    DogGE::Math::Vector3 vec(1,2,3);
    DogGE::Math::Vector3 vec2(vec);
    EXPECT_FLOAT_EQ(vec2[0],1);
    EXPECT_FLOAT_EQ(vec2[1],2);
    EXPECT_FLOAT_EQ(vec2[2],3);
}
TEST(Vector3,setGetX){
    DogGE::Math::Vector3 vec(1,2,3);
    vec.setX(20);
    EXPECT_FLOAT_EQ(vec.getX(),20);
}
TEST(Vector3,setGetY){
    DogGE::Math::Vector3 vec(1,2,3);
    vec.setY(20);
    EXPECT_FLOAT_EQ(vec.getY(),20);
}
TEST(Vector3,setGetZ){
    DogGE::Math::Vector3 vec(1,2,3);
    vec.setZ(20);
    EXPECT_FLOAT_EQ(vec.getZ(),20);
}

TEST(Vector,crossProduct){
    //Numbers from https://de.wikipedia.org/wiki/Kreuzprodukt thanks Wikipedia ;-)
    DogGE::Math::Vector3 vec1(1,2,3);
    DogGE::Math::Vector3 vec2(-7,8,9);
    DogGE::Math::Vector3 vec3 = vec1.crossProduct(vec2);
    EXPECT_FLOAT_EQ(vec3[0],-6);
    EXPECT_FLOAT_EQ(vec3[1],-30);
    EXPECT_FLOAT_EQ(vec3[2],22);
}
TEST(Vector3,crossProduct2){
    DogGE::Math::Vector3 vec1(1,2,3);
    DogGE::Math::Vector3 vec2(-7,8,9);
    DogGE::Math::Vector3 vec3 = vec1 % vec2;
    EXPECT_FLOAT_EQ(vec3[0],-6);
    EXPECT_FLOAT_EQ(vec3[1],-30);
    EXPECT_FLOAT_EQ(vec3[2],22);
}
TEST(Vector3,getAngle){
    DogGE::Math::Vector3 vec1(0,0,1);
    DogGE::Math::Vector3 vec2(0,1,1);
    float angle = DogGE::Math::Vector3::getAngle(vec1,vec2);
    EXPECT_FLOAT_EQ(angle,3.141592653589f /4.0f);  
}
TEST(Vector3,distance){
    DogGE::Math::Vector3 vec1(0,0,1);
    DogGE::Math::Vector3 vec2(0,0,-1);
    float distance = DogGE::Math::Vector3::distance(vec1,vec2);
    EXPECT_FLOAT_EQ(distance, 2);
}
TEST(Vector3,dot){
    DogGE::Math::Vector3 vec1(1,2,3);
    DogGE::Math::Vector3 vec2(-7,8,9);
    float dot3 = DogGE::Math::Vector3::dot3(vec1,vec2);
    EXPECT_FLOAT_EQ(dot3, 36);
}