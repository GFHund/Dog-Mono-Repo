#include <Vector3.h>

namespace DogGE{
    namespace Math{
        //CVector3
        //-----------------------------------
        Vector3::Vector3()
        : Vector()
        {
        }
        Vector3::Vector3(float x,float y,float z)
        : Vector()
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }
        Vector3::Vector3(const Vector<3>& vector)
        {
            vec[0] = vector.getValue(0);
            vec[1] = vector.getValue(1);
            vec[2] = vector.getValue(2);
        }
        void Vector3::setX(float value)
        {
            vec[0] = value;
        }
        void Vector3::setY(float value)
        {
            vec[1] = value;
        }
        void Vector3::setZ(float value)
        {
            vec[2] = value;
        }

        void Vector3::set(Vector3* vecToCopy)
        {
            vec[0] = vecToCopy->getX();
            vec[1] = vecToCopy->getY();
            vec[2] = vecToCopy->getZ();
        }
        void Vector3::set(Vector3 vecToCopy)
        {
            vec[0] = vecToCopy.getX();
            vec[1] = vecToCopy.getY();
            vec[2] = vecToCopy.getZ();
        }

        float Vector3::getX()
        {
            return vec[0];
        }
        float Vector3::getY()
        {
            return vec[1];
        }
        float Vector3::getZ()
        {
            return vec[2];
        }

        double Vector3::getLength3()
        {
            return getLength();
        }

        Vector3 Vector3::crossProduct(Vector3 vector)
        {
            Vector3 ret;
            ret[0] = vec[1]*vector[2] - vec[2]*vector[1];
            ret[1] = vec[2]*vector[0] - vec[0]*vector[2];
            ret[2] = vec[0]*vector[1] - vec[1]*vector[0];
            return ret;
        }

        Vector3 Vector3::operator%(Vector3 vector)
        {
            return crossProduct(vector);
        }
        /*
        bool Vector3::operator==(Vector3 vector)
        {
            Vector3 diff = (*this)-vector;
            return (std::abs(diff.getX()) < FLT_EPSILON ) &&
                    (std::abs(diff.getY()) < FLT_EPSILON ) &&
                    (std::abs(diff.getZ()) < FLT_EPSILON );
        }
        */

        float Vector3::getAngle(Vector3 a,Vector3 b)
        {
            float skalar = a*b;
            return acos(skalar / (a.getLength()*b.getLength()));
        }

        double Vector3::angle(Vector3 vec1,Vector3 vec2)
        {
            return getAngle(vec1,vec2);
        }

        double Vector3::distance(Vector3 vecA,Vector3 vecB)
        {
            return (vecB - vecA).getLength();
        }

        double Vector3::dot3(Vector3 vec1,Vector3 vec2)
        {
            return vec1.getX() * vec2.getX() + 
                vec1.getY() * vec2.getY() +
                vec1.getZ() * vec2.getZ();
        }

        Vector3 operator*(double skalar,Vector3 vec)
        {
            Vector3 ret;
            for(int i=0;i<3;i++)
            {
                ret[i] = vec[i] * skalar;
            }
            return ret;
        }
    }
}