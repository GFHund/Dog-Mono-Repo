#include <gtest/gtest.h>
#include <Matrix.h>
#include <Vector.h>

TEST(Matrix,Constructor1){
    DogGE::Math::Matrix<2,2> mat;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            EXPECT_FLOAT_EQ(mat.getEntity(i,j),0);
        }
    }
}
TEST(Matrix,Constructor2_1){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix,Constructor2_2){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix,Constructor3_1){
    float matArr[] = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr,4);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix,Constructor3_2){
    float matArr[] = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr,4);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(Matrix,Constructor3_3){
    float matArr[] = {1,2};
    DogGE::Math::Matrix<2,2> mat(true,matArr,2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
}
TEST(Matrix,Constructor3_4){
    float matArr[] = {1,2};
    DogGE::Math::Matrix<2,2> mat(false,matArr,2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
}
TEST(Matrix,getSetEntity){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    mat.setEntity(0,1,20);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),20);
}
TEST(Matrix,getSetEntityExceptions){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    EXPECT_THROW(mat.setEntity(0,2,20),DogGE::Math::OutOfBoundsException);
    EXPECT_THROW(mat.setEntity(2,0,20),DogGE::Math::OutOfBoundsException);
    EXPECT_THROW(mat.getEntity(0,2),DogGE::Math::OutOfBoundsException);
    EXPECT_THROW(mat.getEntity(2,0),DogGE::Math::OutOfBoundsException);
}
TEST(Matrix,getArray1){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    float retArr[4];
    mat.getArray(retArr,false);
    EXPECT_FLOAT_EQ(retArr[0],1);
    EXPECT_FLOAT_EQ(retArr[1],2);
    EXPECT_FLOAT_EQ(retArr[2],3);
    EXPECT_FLOAT_EQ(retArr[3],4);
}
TEST(Matrix,getArray2){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    std::array<float,4>retArr = mat.getArray(false);
    EXPECT_FLOAT_EQ(retArr[0],1);
    EXPECT_FLOAT_EQ(retArr[1],2);
    EXPECT_FLOAT_EQ(retArr[2],3);
    EXPECT_FLOAT_EQ(retArr[3],4);
}
TEST(Matrix,getArray3){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    float retArr[4];
    mat.getArray(retArr,false);
    EXPECT_FLOAT_EQ(retArr[0],1);
    EXPECT_FLOAT_EQ(retArr[1],3);
    EXPECT_FLOAT_EQ(retArr[2],2);
    EXPECT_FLOAT_EQ(retArr[3],4);
}
TEST(Matrix,getArray4){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    std::array<float,4>retArr = mat.getArray(true);
    EXPECT_FLOAT_EQ(retArr[0],1);
    EXPECT_FLOAT_EQ(retArr[1],3);
    EXPECT_FLOAT_EQ(retArr[2],2);
    EXPECT_FLOAT_EQ(retArr[3],4);
}
TEST(Matrix,transpose){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    DogGE::Math::Matrix<2,2> mat2 = mat.transpose();
    EXPECT_FLOAT_EQ(mat2.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,1),4);
}
TEST(Matrix,addition){
    std::array<float,4> matArr = {1,2,3,4};
    std::array<float,4> matArr2 = {10,10,10,10};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    DogGE::Math::Matrix<2,2> mat2(true,matArr2);
    DogGE::Math::Matrix<2,2> mat3 = mat + mat2;
    EXPECT_FLOAT_EQ(mat3.getEntity(0,0),11);
    EXPECT_FLOAT_EQ(mat3.getEntity(0,1),12);
    EXPECT_FLOAT_EQ(mat3.getEntity(1,0),13);
    EXPECT_FLOAT_EQ(mat3.getEntity(1,1),14);
}
TEST(Matrix,multiply){
    std::array<float,6> matArr = {3,2,1,1,0,2};
    std::array<float,6> matArr2 = {1,2,0,1,4,0};
    DogGE::Math::Matrix<3,2> mat1(false,matArr);
    DogGE::Math::Matrix<2,3> mat2(false,matArr2);
    DogGE::Math::Matrix<2,2> mat3 = mat1*mat2;   
    EXPECT_FLOAT_EQ(mat3.getEntity(0,0),7);
    EXPECT_FLOAT_EQ(mat3.getEntity(0,1),9);
    EXPECT_FLOAT_EQ(mat3.getEntity(1,0),8);
    EXPECT_FLOAT_EQ(mat3.getEntity(1,1),2);
}
TEST(Matrix,multiplyVector){
    std::array<float,4> matArr = {1,2,3,4};
    std::array<float,2> vecArr = {1,2};
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    DogGE::Math::Vector<2> vec(vecArr);
    DogGE::Math::Vector<2> vec2 = mat * vec;
    EXPECT_FLOAT_EQ(vec2[0],matArr[0]*vecArr[0]+matArr[1]*vecArr[1]);
    EXPECT_FLOAT_EQ(vec2[1],matArr[2]*vecArr[0]+matArr[3]*vecArr[1]);
}
TEST(Matrix,multiplyScalar){
    std::array<float,4> matArr = {1,2,3,4};
    float scalar = 5;
    DogGE::Math::Matrix<2,2> mat(false,matArr);
    DogGE::Math::Matrix<2,2> mat2 = mat*scalar;
    EXPECT_FLOAT_EQ(mat2.getEntity(0,0),5);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,1),15);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,0),10);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,1),20);
}
TEST(Matrix,getRowNum){
    std::array<float,6> matArr = {1,2,3,4,5,6};
    DogGE::Math::Matrix<2,3> mat(false,matArr);
    EXPECT_EQ(mat.getRowNum(),3);
}
TEST(Matrix,getColumnNum){
    std::array<float,6> matArr = {1,2,3,4,5,6};
    DogGE::Math::Matrix<3,2> mat(false,matArr);
    EXPECT_EQ(mat.getColumnNum(),3);
}
TEST(Matrix,clone){
    std::array<float,6> matArr = {1,2,3,4,5,6};
    DogGE::Math::Matrix<2,3> mat(true,matArr);
    DogGE::Math::Matrix<2,3> mat2 = mat.clone();
    EXPECT_FLOAT_EQ(mat2.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,2),3);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,0),4);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,1),5);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,2),6);
}
TEST(Matrix,equal){
    std::array<float,6> matArr = {1,2,3,4,5,6};
    std::array<float,6> matArr2 = {4,5,6,7,8,9};
    DogGE::Math::Matrix<2,3> mat(true,matArr);
    DogGE::Math::Matrix<2,3> mat2 = mat.clone();
    DogGE::Math::Matrix<2,3> mat3(true,matArr2);
    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat == mat3);
}