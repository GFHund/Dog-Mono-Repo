#include <gtest/gtest.h>
#include <Matrix3.h>
#include <Exceptions/MathOperationForbiddenException.h>

TEST(Matrix3,constructor1){
    DogGE::Math::Matrix3 mat;
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),0);
}
TEST(Matrix3,Constructor2_1){
    float matArr[] = {1,2,3,4,5,6,7,8,9};
    DogGE::Math::Matrix3 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),3);

    EXPECT_FLOAT_EQ(mat.getEntity(1,0),4);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),6);

    EXPECT_FLOAT_EQ(mat.getEntity(2,0),7);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),8);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),9);
}
TEST(Matrix3,Constructor2_2){
    float matArr[] = {1,2,3,4,5,6,7,8,9};
    DogGE::Math::Matrix3 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(2,0),3);

    EXPECT_FLOAT_EQ(mat.getEntity(0,1),4);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),6);

    EXPECT_FLOAT_EQ(mat.getEntity(0,2),7);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),8);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),9);
}
TEST(Matrix3,Constructor3_1){
    std::array<float,9> matArr = {1,2,3,4,5,6,7,8,9};
    DogGE::Math::Matrix3 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),3);

    EXPECT_FLOAT_EQ(mat.getEntity(1,0),4);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),6);

    EXPECT_FLOAT_EQ(mat.getEntity(2,0),7);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),8);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),9);
}
TEST(Matrix3,Constructor3_2){
    std::array<float,9> matArr = {1,2,3,4,5,6,7,8,9};
    DogGE::Math::Matrix3 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(2,0),3);

    EXPECT_FLOAT_EQ(mat.getEntity(0,1),4);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),6);

    EXPECT_FLOAT_EQ(mat.getEntity(0,2),7);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),8);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),9);
}
TEST(Matrix3,Inverse){
    std::array<float,9> matArr = {1,2,3,4,5,6,7,8,9};
    DogGE::Math::Matrix3 mat(false,matArr);
    EXPECT_THROW(mat.inverse(),DogGE::Math::MathOperationForbiddenException);
}
TEST(Matrix3,Inverse2){
    std::array<float,9> matArr = {0,1,2,3,2,1,1,1,0};
    DogGE::Math::Matrix3 mat(false,matArr);
    DogGE::Math::Matrix3 mat2 = mat.inverse();
    DogGE::Math::Matrix3 mat3 = mat * mat2;
    EXPECT_TRUE(mat3 == DogGE::Math::SquareMatrix<3>::getIdentity());
}
TEST(Matrix3,Determinant){
    std::array<float,9> matArr = {0,1,2,3,2,1,1,1,0};
    DogGE::Math::Matrix3 mat(false,matArr);
    float val = mat.determinant();
    EXPECT_EQ(val,3);
}