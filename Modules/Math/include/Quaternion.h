/*
Description:
	
*/

#ifndef __QUATERNION__
#define __QUATERNION__
#include <Matrix4.h>
#include <Vector3.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace DogGE
{
	namespace Math{
		class Quaternion
		{
			private:
				float components[4];
				
			public:
				Quaternion();
				Quaternion(float x0,float x1,float x2,float x3);
				Quaternion(Vector3 rotationAxis,float angle);
				Quaternion operator +(Quaternion sum);
				Quaternion operator *(Quaternion quat);
				Vector3 operator *(Vector3 vec);
				float& operator [](int index);
				Quaternion conjugate();
				Quaternion inverse();
				Matrix4 getMatrix();
				void getAxisAngle(Vector3& axis,float& angle);
				float getW();
				float getX();
				float getY();
				float getZ();
				void setW(float w);
				void setX(float x);
				void setY(float y);
				void setZ(float z);
		};
	}
	
}

#ifdef __cplusplus
}
#endif

#endif