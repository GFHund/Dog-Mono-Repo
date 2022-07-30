#ifndef __MATRIX_4__
#define __MATRIX_4__

#include <Matrix.h>
#include <SquareMatrix.h>
#include <Matrix3.h>
#include <Vector3.h>




namespace DogGE{
    namespace Math{
        class Matrix4:public SquareMatrix<4>
        {
            protected:
            Matrix3 getPartMatrix(int column,int row);
            Matrix4 adjugateMatrix();
            public:
            Matrix4();
            Matrix4(bool column,float* arr);
            Matrix4(bool column,std::array<float,16> arr);
            Matrix4(Matrix<4u,4u> mat);

            Vector3 multiplyVec3(Vector3 vec);
            Matrix4 inverse();
            //Matrix3 getRotationMatrix();
            float determinant();
            //static CMatrix4 getTranslationMatrix(CVector3 vec);
        };
    }
}

#endif 