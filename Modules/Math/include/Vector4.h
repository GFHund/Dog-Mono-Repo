#ifndef __VECTOR_4__
#define __VECTOR_4__

#include <Vector.h>
#include <Vector3.h>

namespace DogGE{
    namespace Math{
        class Vector4:public Vector<4>
        {
        public:
            Vector4();
            Vector4(float x,float y,float z,float w);
            Vector4(const Vector<4>& vector);
            Vector4(Vector3 vec);
            void setX(float value);
            void setY(float value);
            void setZ(float value);
            void setW(float value);
            float getX();
            float getY();
            float getZ();
            float getW();
        };
    }
}

#endif 