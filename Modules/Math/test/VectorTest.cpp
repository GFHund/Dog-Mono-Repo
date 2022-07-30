#include <gtest/gtest.h>
#include <Vector.h>

TEST(Vector,constructor1){
    std::array<float,2> arr = {3,4};

    DogGE::Math::Vector<2> vec(arr);

    EXPECT_FLOAT_EQ(vec.getValue(0),3);
    EXPECT_FLOAT_EQ(vec.getValue(1),4);
}
TEST(Vector,constructor2){
    float test[] = {3,4};
    DogGE::Math::Vector<2> vec(test);

    EXPECT_FLOAT_EQ(vec.getValue(0),3);
    EXPECT_FLOAT_EQ(vec.getValue(1),4);
}
TEST(Vector,constructor3){
    DogGE::Math::Vector<2> vec;
    EXPECT_FLOAT_EQ(vec.getValue(0),0);
    EXPECT_FLOAT_EQ(vec.getValue(1),0);
}

TEST(Vector,getArray){
    float test[] = {3,4};
    DogGE::Math::Vector<2> vec(test);
    float test2[2]; 
    vec.getArray(test2);
    for(int i=0;i<2;i++){
        EXPECT_FLOAT_EQ(test[i],test2[i]);
    }
}
TEST(Vector,VectorAddition){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};

    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3 = vec1 + vec2;
    EXPECT_FLOAT_EQ(vec3.getValue(0),test[0] + test2[0]);
    EXPECT_FLOAT_EQ(vec3.getValue(1),test[1] + test2[1]);
}
TEST(Vector,VectorSubtraction){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};

    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3 = vec2 - vec1;
    EXPECT_FLOAT_EQ(vec3.getValue(0),test2[0] - test[0]);
    EXPECT_FLOAT_EQ(vec3.getValue(1),test2[1] - test[1]);
}
TEST(Vector,product){
    std::array<float,2> test = {3,4};
    float number = 5;
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> result = vec1 * number;
    EXPECT_FLOAT_EQ(result.getValue(0),test[0] * number);
    EXPECT_FLOAT_EQ(result.getValue(1),test[1] * number);
}
TEST(Vector,dotProduct){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    float number = vec1 * vec2;
    EXPECT_FLOAT_EQ(number, test[0] * test2[0] + test[1] * test2[1]);
}
TEST(Vector,division){
    std::array<float,2> test = {15,20};
    DogGE::Math::Vector<2> vec1(test);
    float number = 5;
    DogGE::Math::Vector<2> result = vec1 / number;
    EXPECT_FLOAT_EQ(result.getValue(0),test[0] / number);
    EXPECT_FLOAT_EQ(result.getValue(1),test[1] / number);
}
TEST(Vector,addEqual){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    vec1 += vec2;
    EXPECT_FLOAT_EQ(vec1.getValue(0),test[0] + test2[0]);
    EXPECT_FLOAT_EQ(vec1.getValue(1),test[1] + test2[1]);
}
TEST(Vector,subEqual){
    std::array<float,2> test = {9,11};
    std::array<float,2> test2 = {6,7};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    vec1 -= vec2;
    EXPECT_FLOAT_EQ(vec1.getValue(0),test[0] - test2[0]);
    EXPECT_FLOAT_EQ(vec1.getValue(1),test[1] - test2[1]);
}
TEST(Vector,productEqual){
    std::array<float,2> test = {3,4};
    float number = 5;
    DogGE::Math::Vector<2> vec1(test);
    vec1 *= number;
    EXPECT_FLOAT_EQ(vec1.getValue(0),test[0] * number);
    EXPECT_FLOAT_EQ(vec1.getValue(1),test[1] * number);
}
TEST(Vector,divisionEqual){
    std::array<float,2> test = {15,20};
    DogGE::Math::Vector<2> vec1(test);
    float number = 5;
    vec1 /= number;
    EXPECT_FLOAT_EQ(vec1.getValue(0),test[0] / number);
    EXPECT_FLOAT_EQ(vec1.getValue(1),test[1] / number);
}
TEST(Vector,Equal){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};
    std::array<float,2> test3 = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3(test3);
    EXPECT_TRUE(vec1 == vec3);
    EXPECT_FALSE(vec1 == vec2);
}
TEST(Vector,NotEqual){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,7};
    std::array<float,2> test3 = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3(test3);
    EXPECT_FALSE(vec1 != vec3);
    EXPECT_TRUE(vec1 != vec2);
}
TEST(Vector,arrayIndexOperator){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_FLOAT_EQ(vec1[0],3);
    EXPECT_FLOAT_EQ(vec1[1],4);
}
TEST(Vector,arrayIndexOperatorException){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_THROW(vec1[2],DogGE::Math::OutOfBoundsException);
    EXPECT_THROW(vec1[3],DogGE::Math::OutOfBoundsException);
}
TEST(Vector,minFunc){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,2};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3 = vec1.minFunc(vec2);
    EXPECT_FLOAT_EQ(vec3[0],3);
    EXPECT_FLOAT_EQ(vec3[1],2);
}
TEST(Vector,maxFunc){
    std::array<float,2> test = {3,4};
    std::array<float,2> test2 = {6,2};
    DogGE::Math::Vector<2> vec1(test);
    DogGE::Math::Vector<2> vec2(test2);
    DogGE::Math::Vector<2> vec3 = vec1.maxFunc(vec2);
    EXPECT_FLOAT_EQ(vec3[0],6);
    EXPECT_FLOAT_EQ(vec3[1],4);
}
TEST(Vector,getValue){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_FLOAT_EQ(vec1.getValue(0),3);
    EXPECT_FLOAT_EQ(vec1.getValue(1),4);
}
TEST(Vector,getValueException){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_THROW(vec1.getValue(2),DogGE::Math::OutOfBoundsException);
    EXPECT_THROW(vec1.getValue(3),DogGE::Math::OutOfBoundsException);
}
TEST(Vector,getLength){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_FLOAT_EQ(vec1.getLength(),sqrt(3*3+4*4));
}
TEST(Vector,normalize){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    vec1.normalize();
    EXPECT_FLOAT_EQ(vec1.getValue(0), 3.0f / 5.0f);
    EXPECT_FLOAT_EQ(vec1.getValue(1), 4.0f / 5.0f);
}
TEST(Vector,getSize){
    std::array<float,2> test = {3,4};
    DogGE::Math::Vector<2> vec1(test);
    EXPECT_EQ(vec1.getSize(),2);

    std::array<float,3> test2 = {1,2,3};
    DogGE::Math::Vector<3> vec2(test2);
    EXPECT_EQ(vec2.getSize(),3);
}