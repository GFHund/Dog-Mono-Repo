#include <Matrix4.h>
#include <Vector4.h>
#include <math.h>
#include <Exceptions/MathOperationForbiddenException.h>

namespace DogGE
{
	namespace Math{
		Matrix4::Matrix4()
        : SquareMatrix()
        {
        }

        Matrix4::Matrix4(bool column,float* arr)
        : SquareMatrix(column,arr)
        {
        }

        Matrix4::Matrix4(bool column,std::array<float,16> arr)
        : SquareMatrix(column,arr)
        {}

        Matrix4::Matrix4(Matrix<4u,4u> mat)
        {
            for(int i = 0;i<getColumnNum();i++)
            {
                for(int k =0;k<getRowNum();k++)
                {
                    setEntity(i,k,mat.getEntity(i,k));
                }
            }
        }

        Vector3 Matrix4::multiplyVec3(Vector3 vec)
        {
            Vector4 vec4 = Vector4(vec);
            Matrix4 mat = (*this);
            Vector4 ret4 =  mat * vec4;
            return Vector3(ret4.getX(),ret4.getY(),ret4.getZ());
        }
        /*
        Matrix3 Matrix4::getRotationMatrix()
        {
            Matrix3 ret;
            ret.setEntity(0,0,getEntity(0,0));
            ret.setEntity(0,1,getEntity(0,1));
            ret.setEntity(0,2,getEntity(0,2));

            ret.setEntity(1,0,getEntity(1,0));
            ret.setEntity(1,1,getEntity(1,1));
            ret.setEntity(1,2,getEntity(1,2));

            ret.setEntity(2,0,getEntity(2,0));
            ret.setEntity(2,1,getEntity(2,1));
            ret.setEntity(2,2,getEntity(2,2));

            return ret;
        }
        */
       float Matrix4::determinant(){
           float column = 0;
           std::array<float,4> result={0,0,0,0};
           for(int i=0;i<4;i++){
               Matrix3 mat = getPartMatrix(column,i);
               /*
               int offset = 0;
               for(int k=0;k<4;k++){
                   if(k == i){
                       offset -= 1;
                        continue;
                    }
                    for(int j= 1;j<4;j++){
                       mat.setEntity(j-1,k+offset,getEntity(j,k));
                   }
               }
               */
               result[i] = getEntity(column,i) * mat.determinant();
           }
           return result[0] + result[1] - result[2] + result[3] - result[4];
       }
       Matrix4 Matrix4::adjugateMatrix(){
           Matrix4 ret;
           for(int x = 0;x<4;x++){
               for(int y = 0;y<4;y++){
                   Matrix3 partMatrix = getPartMatrix(x,y);
                   float det = partMatrix.determinant();
                   if((x % 2) == 0){
                       if((y % 2) == 0){
                           ret.setEntity(x,y,det);
                       } else {
                           ret.setEntity(x,y,-det);
                       }
                   } else {
                       if((y % 2) == 0){
                           ret.setEntity(x,y,-det);
                       } else {
                           ret.setEntity(x,y,det);
                       }
                   }
               }
           }
           return ret;
       }
       Matrix3 Matrix4::getPartMatrix(int column,int row){
           
           std::array<float,9> matArr;
           int index = 0;
           for(int x = 0;x<4;x++){
               for(int y=0;y<4;y++){
                   if(x == column){
                       continue;
                   }
                   if(y == row){
                       continue;
                   }

                   matArr[index] = this->getEntity(x,y);

                   index++;
               }
           }
           return Matrix3(true,matArr);
       }
       Matrix4 Matrix4::inverse(){
           float determinant = this->determinant();
            if(abs(determinant) == 0){
                throw MathOperationForbiddenException("Determinant must not equal 0 to inverse a Matrix");
            }
            float det = 1.0f/determinant;
            Matrix4 ret = this->adjugateMatrix();
            ret = ret.transpose();
            ret = ret * det;
            return ret;
       }
	}
}