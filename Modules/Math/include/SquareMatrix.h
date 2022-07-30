#ifndef __SQUARE_MATRIX__
#define __SQUARE_MATRIX__

#include <Matrix.h>
#include <vector>

namespace DogGE{
    namespace Math{
        template<std::size_t N>
        class SquareMatrix:public Matrix<N,N>
        {
            protected:
            SquareMatrix<N> swapLines(int row1,int row2);
            std::vector<std::pair<int,SquareMatrix<N>>> createPermutation(
                int depth=0,
                std::vector<std::pair<int,SquareMatrix<N>>> prefoundPermutation = std::vector<std::pair<int,SquareMatrix<N>>>());
            public:
            SquareMatrix();
            SquareMatrix(bool column,float* arr);
            SquareMatrix(bool column,std::array<float,N*N> arr);
            SquareMatrix(const Matrix<N,N>& mat);
            SquareMatrix<N> inverse();
            static SquareMatrix<N> getIdentity();
            //static SquareMatrix<N> getTranslationMatrix(Vector<N> vec);
            SquareMatrix<N-1> getPartMatrix(int column,int row);
            float determinant();
            
        };

        //-------------------------------------------------------
        template<std::size_t N>
        SquareMatrix<N>::SquareMatrix()
        :Matrix<N,N>()
        {
        }

        template<std::size_t N>
        SquareMatrix<N>::SquareMatrix(bool column,float* arr)
        : Matrix<N,N>(column,arr,N*N)
        {
        }

        template<std::size_t N>
        SquareMatrix<N>::SquareMatrix(bool column,std::array<float,N*N> arr)
        : Matrix<N,N>(column,arr)
        {
        }

        template<std::size_t N>
        SquareMatrix<N>::SquareMatrix(const Matrix<N,N>& mat)
        {
            for(int i=0;i<N;i++)
            {
                for(int k=0;k<N;k++)
                {
                    this->setEntity(i,k,mat.getEntity(i,k));
                }
            }
        }

        template<std::size_t N>
        SquareMatrix<N> SquareMatrix<N>::inverse()
        {
            /*
            if(getColumnNum() != getRowNum())
            {
                //failure
            }
            */
            SquareMatrix<N> ret;
            SquareMatrix<N> cloneCMatrix = this->clone();
            for(int i = 0;i<this->getColumnNum();i++)
            {
                ret.setEntity(i,i,1);
            }

            for(int i=0;i<this->getColumnNum();i++)
            {
                float temp = cloneCMatrix.getEntity(i,i);
                if(temp!=1 && temp!=0)
                {
                    for(int j=i;j<this->getColumnNum();j++)
                    {
                        cloneCMatrix.setEntity(j,i,cloneCMatrix.getEntity(j,i)/temp);
                    }
                    for(int j=0;j<this->getColumnNum();j++)
                    {
                        float temp1 = ret.getEntity(j,i);
                        ret.setEntity(j,i,temp1/temp);
                    }
                }
                else if(temp == 0)
                {
                    //failure
                }

                for(int k=i+1;k<this->getColumnNum();k++)
                {
                    temp = cloneCMatrix.getEntity(i,k)*-1;
                    for(int j=0;j<this->getColumnNum();j++)
                    {
                        cloneCMatrix.setEntity(j,k,cloneCMatrix.getEntity(j,k)+temp*cloneCMatrix.getEntity(j,i));
                    }
                    for(int j=0;j<this->getColumnNum();j++)
                    {
                        ret.setEntity(j,k,ret.getEntity(j,k)+temp*ret.getEntity(j,i));
                    }
                }
            }

            for(int i = this->getColumnNum()-1;i>=0;i--)
            {
                for(int k=i-1;k>=0;k--)
                {
                    float temp = cloneCMatrix.getEntity(i,k)*-1;
                    for(int j=i;j>=0 && j!=k;j--)
                    {
                        cloneCMatrix.setEntity(j,k,cloneCMatrix.getEntity(j,k)+cloneCMatrix.getEntity(j,i)*temp);
                    }
                    for(int j=0;j<this->getColumnNum();j++)
                    {
                        ret.setEntity(j,k,ret.getEntity(j,k)+ret.getEntity(j,i)*temp);
                    }
                }
            }
            return ret;
        }

        template<std::size_t N>
        SquareMatrix<N> SquareMatrix<N>::getIdentity()
        {
            SquareMatrix<N> ret;
            for(int i=0;i<ret.getColumnNum();i++)
            {
                ret.setEntity(i,i,1);
            }
            return ret;
        }
        /*
        template<std::size_t N>
        SquareMatrix<N> SquareMatrix<N>::getTranslationMatrix(Vector<N> vec)
        {
            SquareMatrix<N> ret = SquareMatrix<N>::getIdentity();
            for(int i=0;i < N;i++)
            {
                ret.setEntity(N-1,i,vec[i]);
            }
            return ret;
        }
        */
       template<std::size_t N>
       SquareMatrix<N-1> SquareMatrix<N>::getPartMatrix(int column,int row){
           std::array<float,(N-1)*(N-1)> matArr;
           int index = 0;
           for(int x = 0;x<N;x++){
               for(int y=0;y<N;y++){
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
           return SquareMatrix<N-1>(true,matArr);
       }
        
        template<std::size_t N>
        SquareMatrix<N> SquareMatrix<N>::swapLines(int row1,int row2){
            SquareMatrix<N> ret;
            for(int col = 0;col< N;col++){
                for(int row = 0;row < N; row++){
                    int targetRow = row;
                    int sourceRow = row;
                    if(row == row1){
                        targetRow = row2;
                        sourceRow = row1;
                    }
                    else if(row == row2){
                        targetRow = row1;
                        sourceRow = row2;
                    }
                    float val = this->getEntity(col,sourceRow);
                    ret.setEntity(col,targetRow,val);
                }
            }
            return ret;
        }
        template<std::size_t N>
        std::vector<std::pair<int,SquareMatrix<N>>> SquareMatrix<N>::createPermutation(int depth,std::vector<std::pair<int,SquareMatrix<N>>> prefoundPermutation){
            if(depth > N-1){
                return prefoundPermutation;
            }
            if(prefoundPermutation.size() <= 0){
                prefoundPermutation.push_back(std::make_pair(0,*this));
            }
            for(auto permutation:prefoundPermutation){
                for(int i=0;i<N;i++){ // Source Row
                    for(int j=i;j<N;j++){ //Target Row
                        if(i == j) continue;
                        SquareMatrix<N> mat = permutation.second.swapLines(i,j);
                        bool bAlreadyExisting = false;
                        for(auto permutation1:prefoundPermutation){
                            if(permutation1.second == mat){
                                bAlreadyExisting = true;
                            }
                        }
                        if(bAlreadyExisting == false){
                            int sigma = j-i;
                            sigma += permutation.first;
                            prefoundPermutation.push_back(std::make_pair(sigma,mat));
                        }
                    }
                }
            }
            std::vector<std::pair<int,SquareMatrix<N>>> ret = createPermutation(depth+1,prefoundPermutation);
            return ret;
            
        }

       template<std::size_t N>
       float SquareMatrix<N>::determinant(){
           /*
           float ret = 1;
           for(int i = 0;i<N;i++){
               ret *= this->getEntity(i,i);
           }
           for(int i = 0;i<N;i++){
               for(int j = 0;j<N;j++){
                   if(i == j){
                       continue;
                   }
                   SquareMatrix<N> mat = swapLines(i,j);
                   int sigma = 1;
                   if((j-i)%2 != 0){
                       sigma = -1;
                   }
                   float product = 1;
                   for(int k = 0;k<N;k++){
                       product *= mat.getEntity(k,k);
                   }
                   ret += sigma*product;
                }
           }
           */
           std::vector<std::pair<int,SquareMatrix<N>>> permutations = createPermutation();
           float ret = 0;
           for(auto permutation:permutations){
                int sigma = 1;
                if(permutation.first %2 != 0){
                    sigma = -1;
                }
                SquareMatrix<N> mat = permutation.second;
                float product = 1;
                for(int k=0;k<N;k++){
                    product *= mat.getEntity(k,k);
                }
                ret += sigma*product;
           }
           return ret;
           /*
           int column = 0;
           float ret = 0;
           if(N == 2){
               return this->getEntity(0,0) * this->getEntity(1,1) - this->getEntity(1,0) * this->getEntity(0,1);
           } else {
                for(int row = 0;row < N;row++){
                    SquareMatrix<N-1> mat = this->getPartMatrix(column,row);
                    ret += pow(-1,column+row) * this->getEntity(column,row) * mat.determinant();
                }
                return ret;
           }
           */
       }
    }
}

#endif