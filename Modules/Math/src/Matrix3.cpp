#include <Matrix3.h>
#include <Matrix2.h>
#include <math.h>
#include <Exceptions/MathOperationForbiddenException.h>

namespace DogGE
{
	namespace Math{
        Matrix3::Matrix3()
        : SquareMatrix()
        {
        }

        Matrix3::Matrix3(bool column,float* arr)
        : SquareMatrix(column,arr)
        {
        }

        Matrix3::Matrix3(bool column,std::array<float,9> arr)
        : SquareMatrix(column,arr)
        {    
        }

        Matrix3::Matrix3(Matrix<3u,3u> mat)
        {
            for(int i = 0;i<getColumnNum();i++)
            {
                for(int k =0;k<getRowNum();k++)
                {
                    setEntity(i,k,mat.getEntity(i,k));
                }
            }
        }

        Matrix3 Matrix3::inverse()
        {
            //float A,B,C,D,E,F,G,H,I;
            float determinant = this->determinant();
            if(abs(determinant) == 0){
                throw MathOperationForbiddenException("Determinant must not equal 0 to inverse a Matrix");
            }
            float det = 1.0f/determinant;
            Matrix3 ret;
            ret.setEntity(0,0,getEntity(1,1)*getEntity(2,2)-getEntity(2,1)*getEntity(1,2));
            ret.setEntity(1,0,-(getEntity(0,1)*getEntity(2,2)-getEntity(2,1)*getEntity(0,2)));
            ret.setEntity(2,0,(getEntity(0,1)*getEntity(1,2)-getEntity(1,1)*getEntity(0,2)));

            ret.setEntity(0,1,-(getEntity(1,0)*getEntity(2,2) - getEntity(2,0)*getEntity(1,2)));
            ret.setEntity(1,1,getEntity(0,0)*getEntity(2,2) - getEntity(2,0)*getEntity(0,2));
            ret.setEntity(2,1,-(getEntity(0,0)*getEntity(1,2) - getEntity(1,0)*getEntity(0,2)));

            ret.setEntity(0,2,getEntity(1,0)*getEntity(2,1) - getEntity(2,0)*getEntity(1,1));
            ret.setEntity(1,2,-(getEntity(0,0)*getEntity(2,1) - getEntity(2,0)*getEntity(0,1)));
            ret.setEntity(2,2,getEntity(0,0)*getEntity(1,1) - getEntity(1,0)*getEntity(0,1));

            ret = ret.transpose();
            ret = ret*det;
            return ret;
        }
        float Matrix3::determinant()
        {
            std::array<float,4> mat1Arr = {getEntity(1,1),getEntity(2,1),getEntity(1,2),getEntity(2,2)};
            std::array<float,4> mat2Arr = {getEntity(1,0),getEntity(2,0),getEntity(1,2),getEntity(2,2)};
            std::array<float,4> mat3Arr = {getEntity(1,0),getEntity(2,0),getEntity(1,1),getEntity(2,1)};
            Matrix2 mat1 = Matrix2(true,mat1Arr);
            Matrix2 mat2 = Matrix2(true,mat2Arr);
            Matrix2 mat3 = Matrix2(true,mat3Arr);
            float a = getEntity(0,0) * mat1.determinant();
            float b = getEntity(0,1) * mat2.determinant();
            float c = getEntity(0,2) * mat3.determinant();
            return a-b+c;
        }
	}
}