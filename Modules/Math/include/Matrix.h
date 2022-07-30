
#ifndef __MATRIX__
#define __MATRIX__

#include <stdarg.h>
//#include <array>
#include <iostream>

#include <Vector.h>
#include <Exceptions/OutOfBoundsException.h>

namespace DogGE
{
	namespace Math{
		template<std::size_t N,std::size_t M>//N = Spalten M = Zeilen
		class Matrix;

		template<std::size_t N,std::size_t M>
		std::ostream& operator<<(std::ostream& input,const Matrix<N,M>& matrix);

		template<std::size_t N,std::size_t M>
		bool operator==(Matrix<N,M> matrix1,Matrix<N,M> matrix2);

		template<std::size_t N,std::size_t M>//N = Spalten M = Zeilen
		class Matrix
		{
		friend std::ostream& operator<< <>(std::ostream& input,const Matrix<N,M>& matrix);
		protected:
			//std::array<std::array<float,M>,N> mMat;
			float mMat[N][M];

		public:
			Matrix();

			Matrix(bool column,std::array<float,N*M> mat);
			//toDo arr first,second size,last column
			Matrix(bool column,float* arr,int size);
			//CMatrix(bool column,std::array<float,N*M> arr);

			float getEntity(unsigned int column,unsigned int row) const;
			void setEntity(unsigned int column,unsigned int row,float value);

			//std::array<float,M*N> getArray();
			void getArray(float* arr,bool rowFirst);
			std::array<float,N*M> getArray(bool rowFirst);

			Matrix<M,N> transpose();

			Matrix<N,M> operator+(Matrix<N,M> matrix);

			template <std::size_t O>
			Matrix<O,M> operator*(Matrix<O,N> matrix);

			Vector<N> operator*(Vector<N> vector);
			Matrix<N,M> operator*(float skalar);

			//void operator= (CMatrix<N,M> mat);

			int getRowNum();
			int getColumnNum();

			Matrix<N,M> clone();

		};
		template<std::size_t N,std::size_t M>
		std::ostream& operator <<(std::ostream& input,const Matrix<N,M>& matrix)
		{
			//return (input << "[" << vector.getX()<< "\t" << vector.getY()<<"\t" << vector.getZ() <<"]");
			for(int i=0;i<M;i++)
			{
				for(int j=0;j<N;j++)
				{
					input << matrix.getEntity(j,i) << "\t";
				}
				input << std::endl;
			}
			return input;
		}
		template<std::size_t N,std::size_t M>
		bool operator==(Matrix<N,M> matrix1,Matrix<N,M> matrix2)
		{
			bool ret=true;
			for(int i=0;i<N;i++)
			{
				for(int k=0;k<M;k++)
				{
					if(std::abs(matrix1.getEntity(i,k)-matrix2.getEntity(i,k)) > FLT_EPSILON)
					{
						ret = false;
						break;
					}
				}
				if(!ret)
				{
					break;
				}
			}
			return ret;
		}
		template<std::size_t N,std::size_t M>
		Matrix<N,M>::Matrix()
		{
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					mMat[i][j] = 0;
					/*
					if(i==j)
					{
						mat[i][j] = 1;
					}
					else
					{
						mat[i][j] = 0;
					}
					*/
				}
			}
		}
		template<std::size_t N,std::size_t M>
		Matrix<N,M>::Matrix(bool column,std::array<float,N*M> mat){
			
			if(column)
			{
				for(int i=0;i<N;i++)
				{
					for(int j = 0;j<M;j++)
					{
						mMat[i][j] = mat[i*M+j];
					}
				}
			} else {
				for(int j = 0;j<M;j++)
				{
					for(int i=0;i<N;i++)
					{
						mMat[i][j] = mat[i+j*N];
					}
				}
			}
		}

		template<std::size_t N,std::size_t M>
		Matrix<N,M>::Matrix(bool column,float* arr,int size)
		{
			int counter=0;
			if(column)
			{
				for(int i=0;i<N;i++)
				{
					for(int j = 0;j<M;j++)
					{
						if(counter<size)
						{
							mMat[i][j] = arr[i*M+j];
							counter++;
						}
						else
						{
							mMat[i][j] = 0;
						}
					}
				}
			}
			else
			{
				for(int j = 0;j<M;j++)
				{
					for(int i=0;i<N;i++)
					{
						if(counter<size)
						{
							mMat[i][j] = arr[i+j*N];
							counter++;
						}
						else
						{
							mMat[i][j] = 0;
						}
					}
				}
			}
		}
		template<std::size_t N,std::size_t M>
		float Matrix<N,M>::getEntity(unsigned int column,unsigned int row) const
		{
			if(column >= N){
				throw OutOfBoundsException(N,column);
			}
			if(row >= M){
				throw OutOfBoundsException(M,row);
			}
			return mMat[column][row];
		}
		template<std::size_t N,std::size_t M>
		void Matrix<N,M>::setEntity(unsigned int column,unsigned int row,float value)
		{
			if(column >= N){
				throw OutOfBoundsException(N,column);
			}
			if(row >= M){
				throw OutOfBoundsException(M,row);
			}
			mMat[column][row] = value;
		}

		template<std::size_t N,std::size_t M>
		void Matrix<N,M>::getArray(float* arr,bool rowFirst)
		{
			for(int i=0;i<N;i++)//spalten
			{
				for(int j=0;j<M;j++)//zeilen
				{
					if(rowFirst)
					{
						arr[j+i*N] = mMat[i][j];
					}
					else
					{
						arr[i+j*N] = mMat[i][j];
					}
				}
			}
		}
		template<std::size_t N,std::size_t M>
		std::array<float,N*M> Matrix<N,M>::getArray(bool rowFirst){
			std::array<float,N*M> ret;
			for(int i=0;i<N;i++)//spalten
			{
				for(int j=0;j<M;j++)//zeilen
				{
					if(rowFirst)
					{
						ret[j+i*N] = mMat[i][j];
					}
					else
					{
						ret[i+j*N] = mMat[i][j];
					}
				}
			}
			return ret;
		}

		template<std::size_t N,std::size_t M>
		Matrix<M,N> Matrix<N,M>::transpose()
		{
			Matrix<M,N> ret;
			for(int i = 0;i<getColumnNum();i++)
			{
				for(int k =0;k<getRowNum();k++)
				{
					ret.setEntity(k,i,getEntity(i,k));
				}
			}
			return ret;
		}

		template<std::size_t N,std::size_t M>
		Matrix<N,M> Matrix<N,M>::operator+(Matrix<N,M> matrix)
		{
			Matrix<N,M> ret;
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					ret.setEntity(i,j,matrix.getEntity(i,j)+getEntity(i,j));
				}
			}
			return ret;
		}

		template<std::size_t N,std::size_t M>
		template <std::size_t O>
		Matrix<O,M> Matrix<N,M>::operator*(Matrix<O,N> matrix)
		{
			Matrix<O,M> ret;
			if(getColumnNum() != matrix.getRowNum())
			{
				//failure
				return ret;
			}
			for(int i=0;i<M;i++)
			{
				for(int j=0;j<matrix.getColumnNum();j++)
				{
					for(int k = 0;k<N;k++)
					{
						float temp = ret.getEntity(j,i) + getEntity(k,i) * matrix.getEntity(j,k);
						ret.setEntity(j,i,temp);
					}
				}
			}
			return ret;
		}
		//Multiply CMatrix and Vector.
		//toDo: check vector rowSize==CMatrix columnSize
		template<std::size_t N,std::size_t M>
		Vector<N> Matrix<N,M>::operator*(Vector<N> vector)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				for(int k=0;k<N;k++)
				{
					ret[i] += getEntity(k,i) * vector[k];
				}
			}
			return ret;
		}

		template<std::size_t N,std::size_t M>
		Matrix<N,M> Matrix<N,M>::operator*(float skalar)
		{
			Matrix<N,M> ret;
			for(int i = 0;i<getColumnNum();i++)
			{
				for(int k =0;k<getRowNum();k++)
				{
					ret.setEntity(i,k,getEntity(i,k)*skalar);
				}
			}
			return ret;
		}
		template<std::size_t N,std::size_t M>
		int Matrix<N,M>::getRowNum()
		{
			return M;
		}
		template<std::size_t N,std::size_t M>
		int Matrix<N,M>::getColumnNum()
		{
			return N;
		}

		template<std::size_t N,std::size_t M>
		Matrix<N,M> Matrix<N,M>::clone()
		{
			Matrix <N,M> ret;
			for(int i = 0;i<N;i++)
			{
				for(int j = 0;j<M;j++)
				{
					ret.setEntity(i,j,getEntity(i,j));
				}
			}
			return ret;
		}
	}
}

#endif
