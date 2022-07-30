#include <gtest/gtest.h>
#include <Matrix2.h>

TEST(Matrix2,constructor1){
    DogGE::Math::Matrix2 mat;
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
}

TEST(Matrix2,Constructor2_1){
    float matArr[] = {1,2,3,4};
    DogGE::Math::Matrix2 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix2,Constructor2_2){
    float matArr[] = {1,2,3,4};
    DogGE::Math::Matrix2 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix2,Constructor3_1){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix2 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix2,Constructor3_2){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix2 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix2,CopyConstructor){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    DogGE::Math::Matrix2 mat2(mat);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,1),4);
}

TEST(Matrix2,Inverse){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix2 mat(true,matArr);
    DogGE::Math::Matrix2 mat2 = mat.inverse();
    DogGE::Math::Matrix2 mat3 = mat * mat2;
    EXPECT_TRUE(mat3 == DogGE::Math::SquareMatrix<2>::getIdentity());
}
TEST(Matrix2,Determinant){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix2 mat(true,matArr);
    float result = mat.determinant();
    EXPECT_EQ(result,-2);
}