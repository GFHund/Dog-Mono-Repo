#include <gtest/gtest.h>
#include <SquareMatrix.h>

TEST(SquareMatrix,Constructor1){
    DogGE::Math::SquareMatrix<2> mat;
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),0);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),0);
}
TEST(SquareMatrix,Constructor2_1){
    float matArr[] = {1,2,3,4};
    DogGE::Math::SquareMatrix<2> mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(SquareMatrix,Constructor2_2){
    float matArr[] = {1,2,3,4};
    DogGE::Math::SquareMatrix<2> mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(SquareMatrix,Constructor3_1){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::SquareMatrix<2> mat(true,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(SquareMatrix,Constructor3_2){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::SquareMatrix<2> mat(false,matArr);
    EXPECT_FLOAT_EQ(mat.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat.getEntity(1,0),2);
    EXPECT_FLOAT_EQ(mat.getEntity(0,1),3);
    EXPECT_FLOAT_EQ(mat.getEntity(1,1),4);
}
TEST(SquareMatrix,CopyConstructor){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::Matrix<2,2> mat(true,matArr);
    DogGE::Math::SquareMatrix<2> mat2(mat);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,0),1);
    EXPECT_FLOAT_EQ(mat2.getEntity(0,1),2);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,0),3);
    EXPECT_FLOAT_EQ(mat2.getEntity(1,1),4);
}
TEST(SquareMatrix,inverse){
    std::array<float,4> matArr = {1,2,3,4};
    DogGE::Math::SquareMatrix<2> mat2(true,matArr);
    DogGE::Math::SquareMatrix<2> mat3 = mat2.inverse();
    DogGE::Math::SquareMatrix<2> mat4 = mat2 * mat3;
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            if(i == j){
                EXPECT_FLOAT_EQ(mat4.getEntity(i,j),1);
            } else {
                EXPECT_FLOAT_EQ(mat4.getEntity(i,j),0);
            }
        }
    }
}
TEST(SquareMatrix,getIdentiy){
    DogGE::Math::SquareMatrix<2> mat = DogGE::Math::SquareMatrix<2>::getIdentity();
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            if(i == j){
                EXPECT_FLOAT_EQ(mat.getEntity(i,j),1);
            } else {
                EXPECT_FLOAT_EQ(mat.getEntity(i,j),0);
            }
        }
    }
}
/*
TEST(SquareMatrix,getTranslationMatrix){
    std::array<float,3> vecArr = {1,2,3};
    DogGE::Math::Vector<3> vec(vecArr)
    DogGE::Math::SquareMatrix<3> mat = DogGE::Math::SquareMatrix<3>::getTranslationMatrix(vec);
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(i == j){
                EXPECT_FLOAT_EQ(mat.getEntity(i,j),1);
            } else if(){
            } else {
                EXPECT_FLOAT_EQ(mat.getEntity(i,j),0);
            }
        }
    }
}
*/

TEST(SquareMatrix,Determinant1){
    std::array<float,9> matArr = {0,1,2,3,2,1,1,1,0};
    DogGE::Math::SquareMatrix<3> mat(false,matArr);
    float val = mat.determinant();
    EXPECT_EQ(val,3);
}
TEST(SquareMatrix,Determinant2){
    DogGE::Math::SquareMatrix<4> mat = DogGE::Math::SquareMatrix<4>::getIdentity();
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,1);
}
TEST(SquareMatrix,Determinant3){
    DogGE::Math::SquareMatrix<4> mat = DogGE::Math::SquareMatrix<4>::getIdentity();
    mat.setEntity(2,2,4);
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,4);
}
TEST(SquareMatrix,Determinant4){
    std::array<float,16> matArr = {1,2,3,4,0,5,2,3,3,2,1,0,5,0,0,1};
    DogGE::Math::SquareMatrix<4> mat(true,matArr);
    float val = mat.determinant();
    EXPECT_FLOAT_EQ(val,-112);
}