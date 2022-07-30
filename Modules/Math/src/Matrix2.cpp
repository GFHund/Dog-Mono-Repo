#include <Matrix2.h>
#include <math.h>
#include <Exceptions/MathOperationForbiddenException.h>

namespace DogGE
{
	namespace Math{
		Matrix2::Matrix2()
        :SquareMatrix()
        {
        }

        Matrix2::Matrix2(bool column,float* arr)
        : SquareMatrix(column,arr)
        {
        }

        Matrix2::Matrix2(bool column,std::array<float,4> arr)
        : SquareMatrix(column,arr)
        {

        }

        Matrix2::Matrix2(Matrix<2u,2u> mat)
        {
            for(int i = 0;i<getColumnNum();i++)
            {
                for(int k =0;k<getRowNum();k++)
                {
                    setEntity(i,k,mat.getEntity(i,k));
                }
            }
        }

        Matrix2 Matrix2::inverse()
        {
            Matrix2 ret;
            float determinant = this->determinant();
            if(abs(determinant) == 0){
                throw MathOperationForbiddenException("Determinant must not equal 0 to inverse a Matrix");
            }
            float det = 1.0f/determinant;
            ret.setEntity(0,0,getEntity(1,1));
            ret.setEntity(1,0,-getEntity(1,0));
            ret.setEntity(0,1,-getEntity(0,1));
            ret.setEntity(1,1,getEntity(0,0));
            ret = ret * det;
            return ret;
        }

        float Matrix2::determinant()
        {
            return getEntity(0,0)*getEntity(1,1) - getEntity(1,0) * getEntity(0,1);
        }
	}
}