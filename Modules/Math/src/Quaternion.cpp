#include <Quaternion.h>
namespace DogGE
{
	namespace Math{
		Quaternion::Quaternion()
		{
			/*
			for(int i=0;i<4;i++)
			{
				this->components[i] = 1;
			}
			*/
			this->components[0] = 1;//W
			this->components[1] = 0;//X
			this->components[2] = 0;//Y
			this->components[3] = 0;//Z
		}
		Quaternion::Quaternion(float x0,float x1,float x2,float x3)
		{
			this->components[0] = x0;//W
			this->components[1] = x1;//X
			this->components[2] = x2;//Y
			this->components[3] = x3;//Z
		}
		/*
		// Convert from Axis Angle
		void Quaternion::FromAxis(const Vector3 &v, float angle)
		{
			float sinAngle;
			angle *= 0.5f;
			Vector3 vn(v);
			vn.normalise();
		
			sinAngle = sin(angle);
		
			x = (vn.x * sinAngle);
			y = (vn.y * sinAngle);
			z = (vn.z * sinAngle);
			w = cos(angle);
		}
		*/
		Quaternion::Quaternion(Vector3 rotationAxis,float angle)//angle in radian
		//q=cos(a/2)+i(x*sin(a/2)+j(y*sin(a/2)+k(z*sin(a/2)
		{
			
			float a = cos(angle/2.0f);
			float b = sin(angle/2.0f);
			rotationAxis.normalize();
			this->components[0] = a;
			this->components[1] = rotationAxis.getX() * b;
			this->components[2] = rotationAxis.getY() * b;
			this->components[3] = rotationAxis.getZ() * b;
		}

		Quaternion Quaternion::operator +(Quaternion sum)
		{
			Quaternion ret;
			ret[0] = this->components[0] + sum[0];
			ret[1] = this->components[1] + sum[1];
			ret[2] = this->components[2] + sum[2];
			ret[3] = this->components[3] + sum[3];
			return ret;
		}

		Quaternion Quaternion::operator *(Quaternion quat)
		{
			Quaternion ret;
			ret[0] = this->components[0] * quat[0] - this->components[1] * quat[1] - this->components[2] * quat[2] - this->components[3] * quat[3];
			ret[1] = this->components[0] * quat[1] + this->components[1] * quat[0] + this->components[2] * quat[3] - this->components[3] * quat[2];
			ret[2] = this->components[0] * quat[2] - this->components[1] * quat[3] + this->components[2] * quat[0] + this->components[3] * quat[1];
			ret[3] = this->components[0] * quat[3] + this->components[1] * quat[2] - this->components[2] * quat[1] + this->components[3] * quat[0];
			return ret;
		}
		/*
		Vector3 Quaternion::operator* (const Vector3 &vec) const
		{
			Vector3 vn(vec);
			vn.normalise();

			Quaternion vecQuat, resQuat;
			vecQuat.x = vn.x;
			vecQuat.y = vn.y;
			vecQuat.z = vn.z;
			vecQuat.w = 0.0f;

			resQuat = vecQuat * getConjugate();
			resQuat = *this * resQuat;

			return (Vector3(resQuat.x, resQuat.y, resQuat.z));
		}
		*/
		Vector3 Quaternion::operator *(Vector3 vec)
		{
			float length = vec.getLength();
			vec.normalize();
			Quaternion vecQuad = Quaternion(0.0f,vec.getX(),vec.getY(),vec.getZ());
			Quaternion result = vecQuad * conjugate();
			result = (*this) * result;
			Vector3 ret = Vector3(result.getX(), result.getY(), result.getZ());
			ret *= length;
			return ret;
		}
		//index must be between 0 and 4
		float& Quaternion::operator [](int index)
		{
			return this->components[index];
			/*
			if(index < 4)
			{
				
			}
			*/
		}

		Quaternion Quaternion::conjugate()
		{
			return Quaternion(this->components[0],-this->components[1],-this->components[2],-this->components[3]);
		}

		Quaternion Quaternion::inverse()
		{
			Quaternion conju = this->conjugate();
			Quaternion erg = (*this) * conju;
			erg = erg.conjugate();
			return (*this) * erg;
		}
		/*
		// Convert to Matrix
	Matrix4 Quaternion::getMatrix() const
	{
		float x2 = x * x;
		float y2 = y * y;
		float z2 = z * z;
		float xy = x * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;
		float wy = w * y;
		float wz = w * z;

		// This calculation would be a lot more complicated for non-unit length quaternions
		// Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
		//   OpenGL
		return Matrix4( 1.0f - 2.0f * (y2 + z2),| 2.0f * (xy - wz),       | 2.0f * (xz + wy),       | 0.0f,
				2.0f * (xy + wz),               | 1.0f - 2.0f * (x2 + z2),| 2.0f * (yz - wx),       | 0.0f,
				2.0f * (xz - wy),               | 2.0f * (yz + wx),       | 1.0f - 2.0f * (x2 + y2),| 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f)
	}
		*/
		Matrix4 Quaternion::getMatrix()
		{
			float x2 = getX() * getX();
			float y2 = getY() * getY();
			float z2 = getZ() * getZ();
			float xy = getX() * getY();
			float xz = getX() * getZ();
			float yz = getY() * getZ();
			float wx = getW() * getX();
			float wy = getW() * getY();
			float wz = getW() * getZ();
			
			Matrix4 ret;
			ret.setEntity(0,0,1.0f - 2.0f * (y2 + z2));
			ret.setEntity(0,1,       2.0f * (-wz + xy ));
			ret.setEntity(0,2,       2.0f * (xz + wy));
			
			ret.setEntity(1,0,       2.0f * (xy + wz));
			ret.setEntity(1,1,1.0f - 2.0f * (x2 + z2));
			ret.setEntity(1,2,       2.0f * (-wx + yz));
		
			ret.setEntity(2,0,       2.0f * (-wy + xz));
			ret.setEntity(2,1,       2.0f * (yz + wx));
			ret.setEntity(2,2,1.0f - 2.0f * (x2 + y2));
			ret.setEntity(3,3,1.0f);
			/*
			ret.setEntity(0,0,1.0f - 2.0f * (y2 + z2));
			ret.setEntity(0,1,       2.0f * (xy - wz));
			ret.setEntity(0,2,       2.0f * (xz + wy));
			
			ret.setEntity(1,0,       2.0f * (xy + wz));
			ret.setEntity(1,1,1.0f - 2.0f * (x2 + z2));
			ret.setEntity(1,2,       2.0f * (yz - wx));
		
			ret.setEntity(2,0,       2.0f * (xz - wy));
			ret.setEntity(2,1,       2.0f * (yz + wx));
			ret.setEntity(2,2,1.0f - 2.0f * (x2 + y2));
			ret.setEntity(3,3,1.0f);
			*/
			/*
			CMatrix4 ret;
			ret.setEntity(0,0, 1 - 2*this->components[2]*this->components[2] - 2 * this->components[3]*this->components[3]);
			ret.setEntity(0,1,     2*this->components[1]*this->components[2] + 2*this->components[3]*this->components[0]);
			ret.setEntity(0,2,     2*this->components[1]*this->components[3] + 2*this->components[2]*this->components[0]);
			
			ret.setEntity(1,0,     2*this->components[1]*this->components[2] - 2*this->components[3]*this->components[0]);
			ret.setEntity(1,1, 1 - 2*this->components[1]*this->components[1] - 2*this->components[3]*this->components[3]);
			ret.setEntity(1,2,     2*this->components[2]*this->components[3] + 2*this->components[1]*this->components[0]);
			
			ret.setEntity(2,0,    2*this->components[1]*this->components[3] + 2*this->components[2]*this->components[0]);
			ret.setEntity(2,1,    2*this->components[2]*this->components[3] - 2*this->components[1]*this->components[0]);
			ret.setEntity(2,2,1 - 2*this->components[1]*this->components[1] - 2*this->components[2]*this->components[2]);
			ret.setEntity(3,3,1);
			*/
			ret = ret.transpose();
			return ret;
		}
		/*
		// Convert to Axis/Angles
		void Quaternion::getAxisAngle(Vector3 *axis, float *angle)
		{
			float scale = sqrt(x * x + y * y + z * z);
			axis->x = x / scale;
			axis->y = y / scale;
			axis->z = z / scale;
			*angle = acos(w) * 2.0f;
		}
		*/
		void Quaternion::getAxisAngle(Vector3& axis,float& angle)
		{
			float scale = sqrt(getX()*getX() + getY()*getY() + getZ()*getZ());
			axis.setX(getX()/scale);
			axis.setY(getY()/scale);
			axis.setZ(getZ()/scale);
			angle = acos(getW()) * 2.0f;
		}
		
		float Quaternion::getW()
		{
			return this->components[0];
		}
		float Quaternion::getX()
		{
			return this->components[1];
		}
		float Quaternion::getY()
		{
			return this->components[2];
		}
		float Quaternion::getZ()
		{
			return this->components[3];
		}
		void Quaternion::setW(float w)
		{
			this->components[0] = w;
		}
		void Quaternion::setX(float x)
		{
			this->components[1] = x;
		}
		void Quaternion::setY(float y)
		{
			this->components[2] = y;
		}
		void Quaternion::setZ(float z)
		{
			this->components[3] = z;
		}
	}
}