#include <Vector2.h>

namespace DogGE{
    namespace Math{
        //CVector2
        //-----------------------------------
        Vector2::Vector2()
        : Vector()
        {
        }
        Vector2::Vector2(float x,float y)
        : Vector()
        {
            vec[0] = x;
            vec[1] = y;
        }
        Vector2::Vector2(const Vector<2>& vector)
        {
            vec[0] = vector.getValue(0);
            vec[1] = vector.getValue(1);
        }
        void Vector2::setX(float value)
        {
            vec[0] = value;
        }
        void Vector2::setY(float value)
        {
            vec[1] = value;
        }
        float Vector2::getX()
        {
            return vec[0];
        }
        float Vector2::getY()
        {
            return vec[1];
        }
    }
}