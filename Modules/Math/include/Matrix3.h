#ifndef __MATRIX_3__
#define __MATRIX_3__

#include <SquareMatrix.h>

namespace DogGE{
    namespace Math{       
        class Matrix3:public SquareMatrix<3>
        {
            public:
            Matrix3();
            Matrix3(bool column,float* arr);
            Matrix3(bool column,std::array<float,9> arr);
            Matrix3(Matrix<3u,3u> mat);
            Matrix3 inverse();
            float determinant();

        };
    }
}

#endif