#include <Vector4.h>

namespace DogGE{
    namespace Math{
        //CVector4
        //----------------------------------
        Vector4::Vector4()
        : Vector()
        {
        }
        Vector4::Vector4(float x,float y,float z,float w)
        : Vector()
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }

        Vector4::Vector4(const Vector<4>& vector)
        {
            vec[0] = vector.getValue(0);
            vec[1] = vector.getValue(1);
            vec[2] = vector.getValue(2);
            vec[3] = vector.getValue(3);
        }
        Vector4::Vector4(Vector3 vector)
        {
            vec[0] = vector.getValue(0);
            vec[1] = vector.getValue(1);
            vec[2] = vector.getValue(2);
            vec[3] = 1;
        }

        void Vector4::setX(float value)
        {
            vec[0] = value;
        }
        void Vector4::setY(float value)
        {
            vec[1] = value;
        }
        void Vector4::setZ(float value)
        {
            vec[2] = value;
        }
        void Vector4::setW(float value)
        {
            vec[3] = value;
        }
        float Vector4::getX()
        {
            return vec[0];
        }
        float Vector4::getY()
        {
            return vec[1];
        }
        float Vector4::getZ()
        {
            return vec[2];
        }
        float Vector4::getW()
        {
            return vec[3];
        }
    }
}