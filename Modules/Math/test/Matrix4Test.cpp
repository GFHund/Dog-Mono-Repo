#include <gtest/gtest.h>
#include <Matrix4.h>
#include <Exceptions/MathOperationForbiddenException.h>

TEST(Matrix4,constructor1){
    DogGE::Math::Matrix4 mat;
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,3),0);

    EXPECT_FLOAT_EQ(mat.getEntity(1,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,3),0);

    EXPECT_FLOAT_EQ(mat.getEntity(2,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(2,3),0);

    EXPECT_FLOAT_EQ(mat.getEntity(3,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(3,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(3,2),0);
    EXPECT_FLOAT_EQ(mat.getEntity(3,3),0);
}
TEST(Matrix4,Constructor2_1){
    float matArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    DogGE::Math::Matrix4 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),3);
    EXPECT_FLOAT_EQ(mat.getEntity(0,3),4);

    EXPECT_FLOAT_EQ(mat.getEntity(1,0),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),6);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),7);
    EXPECT_FLOAT_EQ(mat.getEntity(1,3),8);

    EXPECT_FLOAT_EQ(mat.getEntity(2,0),9);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),10);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),11);
    EXPECT_FLOAT_EQ(mat.getEntity(2,3),12);

    EXPECT_FLOAT_EQ(mat.getEntity(3,0),13);
    EXPECT_FLOAT_EQ(mat.getEntity(3,1),14);
    EXPECT_FLOAT_EQ(mat.getEntity(3,2),15);
    EXPECT_FLOAT_EQ(mat.getEntity(3,3),16);
}
TEST(Matrix4,Constructor2_2){
    float matArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    DogGE::Math::Matrix4 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(2,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(3,0),4);

    EXPECT_FLOAT_EQ(mat.getEntity(0,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),6);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),7);
    EXPECT_FLOAT_EQ(mat.getEntity(3,1),8);

    EXPECT_FLOAT_EQ(mat.getEntity(0,2),9);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),10);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),11);
    EXPECT_FLOAT_EQ(mat.getEntity(3,2),12);

    EXPECT_FLOAT_EQ(mat.getEntity(0,3),13);
    EXPECT_FLOAT_EQ(mat.getEntity(1,3),14);
    EXPECT_FLOAT_EQ(mat.getEntity(2,3),15);
    EXPECT_FLOAT_EQ(mat.getEntity(3,3),16);
}
TEST(Matrix4,Constructor3_1){
    std::array<float,16> matArr = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    DogGE::Math::Matrix4 mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,2),3);
    EXPECT_FLOAT_EQ(mat.getEntity(0,3),4);

    EXPECT_FLOAT_EQ(mat.getEntity(1,0),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),6);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),7);
    EXPECT_FLOAT_EQ(mat.getEntity(1,3),8);

    EXPECT_FLOAT_EQ(mat.getEntity(2,0),9);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),10);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),11);
    EXPECT_FLOAT_EQ(mat.getEntity(2,3),12);

    EXPECT_FLOAT_EQ(mat.getEntity(3,0),13);
    EXPECT_FLOAT_EQ(mat.getEntity(3,1),14);
    EXPECT_FLOAT_EQ(mat.getEntity(3,2),15);
    EXPECT_FLOAT_EQ(mat.getEntity(3,3),16);
}
TEST(Matrix4,Constructor3_2){
    std::array<float,16> matArr = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    DogGE::Math::Matrix4 mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(2,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(3,0),4);

    EXPECT_FLOAT_EQ(mat.getEntity(0,1),5);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),6);
    EXPECT_FLOAT_EQ(mat.getEntity(2,1),7);
    EXPECT_FLOAT_EQ(mat.getEntity(3,1),8);

    EXPECT_FLOAT_EQ(mat.getEntity(0,2),9);
    EXPECT_FLOAT_EQ(mat.getEntity(1,2),10);
    EXPECT_FLOAT_EQ(mat.getEntity(2,2),11);
    EXPECT_FLOAT_EQ(mat.getEntity(3,2),12);

    EXPECT_FLOAT_EQ(mat.getEntity(0,3),13);
    EXPECT_FLOAT_EQ(mat.getEntity(1,3),14);
    EXPECT_FLOAT_EQ(mat.getEntity(2,3),15);
    EXPECT_FLOAT_EQ(mat.getEntity(3,3),16);
}
TEST(Matrix4,MultiplyVec3){
    DogGE::Math::Matrix4 mat = DogGE::Math::SquareMatrix<4>::getIdentity();
    mat.setEntity(3,0,5);
    mat.setEntity(3,1,6);
    mat.setEntity(3,2,7);
    DogGE::Math::Vector3 vec(1,2,3);
    DogGE::Math::Vector3 vec2 = mat.multiplyVec3(vec);
    EXPECT_FLOAT_EQ(vec2.getX(),6);
    EXPECT_FLOAT_EQ(vec2.getY(),8);
    EXPECT_FLOAT_EQ(vec2.getZ(),10);
}
TEST(Matrix4,Determinant){
    DogGE::Math::Matrix4 mat = DogGE::Math::SquareMatrix<4>::getIdentity();
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,1);
}
TEST(Matrix4,Determinant2){
    DogGE::Math::Matrix4 mat = DogGE::Math::SquareMatrix<4>::getIdentity();
    mat.setEntity(2,2,4);
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,4);
}
TEST(Matrix4,Determinant3){
    std::array<float,16> matArr = {1,2,3,4,0,5,2,3,3,2,1,0,5,0,0,1};
    DogGE::Math::Matrix4 mat(true,matArr);
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,-112);
}
TEST(Matrix4,Inverse1){
    std::array<float,16> matArr = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    DogGE::Math::Matrix4 mat(true,matArr);
    EXPECT_THROW(mat.inverse(),DogGE::Math::MathOperationForbiddenException);
}
TEST(Matrix4,Inverse2){
    std::array<float,16> matArr = {1,2,3,4,0,5,2,3,3,2,1,0,5,0,0,1};
    DogGE::Math::Matrix4 mat(true,matArr);
    DogGE::Math::Matrix4 mat2 = mat.inverse();
    DogGE::Math::Matrix4 mat3 = mat * mat2;
    EXPECT_TRUE(mat3 == DogGE::Math::SquareMatrix<4>::getIdentity());
}