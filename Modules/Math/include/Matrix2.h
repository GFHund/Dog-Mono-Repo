#ifndef __MATRIX_2__
#define __MATRIX_2__

#include <SquareMatrix.h>

namespace DogGE{
    namespace Math{
        class Matrix2:public SquareMatrix<2u>
        {
            public:
            Matrix2();
            Matrix2(bool column,float* arr);
            Matrix2(bool column,std::array<float,4> arr);
            Matrix2(Matrix<2u,2u> mat);
            Matrix2 inverse();
            float determinant();
        };
    }
}

#endif 