#ifndef __VECTOR__
#define __VECTOR__
#include <stdarg.h>
//#include <stddef.h>
#include <math.h>
#include <iostream>
#include <float.h>
#include <cmath>
#include <array>
#include <Exceptions/OutOfBoundsException.h>
//#include "Matrix.h"

namespace DogGE
{
	namespace Math{
		template<std::size_t N>
		class Vector;

		template<std::size_t N>
		std::ostream& operator<<(std::ostream& input,const Vector<N>& vector);

		template<std::size_t N>
		class Vector
		{
		//friend std::ostream& operator<<(std::ostream& input,const CVector<N>& vector);
		friend std::ostream& operator<< <>(std::ostream& input,Vector<N> const& vector);
		protected:
			//std::array<float,N> vec;
			float vec[N];

		public:
			Vector();
			[[deprecated]]
			Vector(int numParam,...);
			Vector(std::array<float,N> arr);
			Vector(float* arr);

			void getArray(float* arr);

			Vector<N> operator+(Vector<N> vector);
			Vector<N> operator-(Vector<N> vector);
			Vector<N> operator*(float skalar);
			float operator*(Vector<N> vector);
			Vector<N> operator/(float skalar);
			void operator+=(Vector<N> vector);
			void operator-=(Vector<N> vector);
			void operator*=(float skalar);
			void operator/=(float skalar);
			bool operator==(Vector<N> vec);
			bool operator!=(Vector<N> vec);
			float& operator[](unsigned int index);
			//Vector<N> crossProduct(Vector<N> vector);
			Vector<N> minFunc(Vector<N> vector);
			Vector<N> maxFunc(Vector<N> vector);

			float getValue(unsigned int index) const;

			float getLength();

			void normalize();

			int getSize();

		};
		//----------------------------------------
		template<std::size_t N>
		std::ostream& operator <<(std::ostream& input,const Vector<N>& vector)
		{
			//return (input << "[" << vector.getX()<< "\t" << vector.getY()<<"\t" << vector.getZ() <<"]");
			input << "[";
			for(int i=0;i<N;i++)
			{
				input << vector.getValue(i) << "\t";
			}
			input << "]";
			return input;
		}

		template<std::size_t N>
		Vector<N>::Vector()
		{
			for(int i=0;i<N;i++)
			{
				this->vec[i] = 0;
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N>::Vector(int numParam,...)
		{
			float value;
			va_list vl;
			va_start(vl,numParam);
			if(numParam >= N)
			{
				for(int i=0;i<N;i++)
				{
					value = (float) va_arg(vl,double);
					this->vec[i] = value;
				}
			}
			else
			{
				for(int i=0;i<numParam;i++)
				{
					value = (float)va_arg(vl,double);
					this->vec[i] = value;
				}
				int rest = N-numParam;
				for(int i=numParam;i<N;i++)
				{
					this->vec[i] = 0;
				}
			}
			va_end(vl);
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N>::Vector(std::array<float,N> arr){
			for(int i=0;i<N;i++)
			{
				this->vec[i] = arr[i];
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N>::Vector(float* arr)
		{
			for(int i=0;i<N;i++)
			{
				this->vec[i] = arr[i];
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::getArray(float* arr)
		{
			for(int i=0;i<N;i++)
			{
				arr[i] = this->vec[i];
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::operator+(Vector<N> vector)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = this->vec[i] + vector[i];
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::operator-(Vector vector)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = this->vec[i] - vector[i];
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::operator*(float skalar)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = this->vec[i] * skalar;
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		float Vector<N>::operator*(Vector<N> vector)
		{
			float ret = 0;
			for(int i=0;i<N;i++)
			{
				ret += this->vec[i] * vector[i];
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::operator/(float skalar)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = this->vec[i] / skalar;
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::operator+=(Vector<N> vector)
		{
			for(int i=0;i<N;i++)
			{
				vec[i]+=vector[i];
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::operator-=(Vector<N> vector)
		{
			for(int i=0;i<N;i++)
			{
				vec[i]-=vector[i];
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::operator*=(float skalar)
		{
			for(int i=0;i<N;i++)
			{
				vec[i]*=skalar;
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::operator/=(float skalar)
		{
			for(int i=0;i<N;i++)
			{
				vec[i]/=skalar;
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		float& Vector<N>::operator[](unsigned int index)
		{
			if(index >= N){
				throw OutOfBoundsException(N,index);
			}
			return this->vec[index];
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::minFunc(Vector<N> vector)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = vec[i] < vector[i] ? vec[i]:vector[i];
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		Vector<N> Vector<N>::maxFunc(Vector<N> vector)
		{
			Vector<N> ret;
			for(int i=0;i<N;i++)
			{
				ret[i] = vec[i] > vector[i] ? vec[i]:vector[i];
			}
			return ret;
		}
		
		//----------------------------------------------------------
		template<std::size_t N>
		float Vector<N>::getValue(unsigned int index) const
		{
			if(index >= N){
				throw OutOfBoundsException(N,index);
			}
			const float value = vec[index];
			return value;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		float Vector<N>::getLength()
		{
			float ret = 0;
			for(int i=0;i<N;i++)
			{
				ret += this->vec[i] * this->vec[i];
			}
			ret = sqrt(ret);
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		void Vector<N>::normalize()
		{
			float length = getLength();
			for(int i=0;i<N;i++)
			{
				this->vec[i] /= length;
			}
		}
		//----------------------------------------------------------
		template<std::size_t N>
		int Vector<N>::getSize()
		{
			return N;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		bool Vector<N>::operator==(Vector<N> vec)
		{
			bool ret = true;
			for(int i=0;i<N;i++)
			{
				if(std::abs(getValue(i) - vec[i]) > FLT_EPSILON)
				{
					ret = false;
					break;
				}
			}
			return ret;
		}
		//----------------------------------------------------------
		template<std::size_t N>
		bool Vector<N>::operator!=(Vector<N> vec)
		{
			bool ret = false;
			for(int i=0;i<N;i++)
			{
				if(std::abs(getValue(i) - vec[i]) > FLT_EPSILON)
				{
					ret = true;
					break;
				}
			}
			return ret;
		}
	}
}

#endif
