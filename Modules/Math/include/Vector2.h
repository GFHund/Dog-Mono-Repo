#ifndef __VECTOR_2__
#define __VECTOR_2__
#pragma once

#include <Vector.h>

namespace DogGE{
    namespace Math{
        class Vector2:public Vector<2>
        {
        public:
            Vector2();
            Vector2(float x,float y);
            Vector2(const Vector<2>& vector);
            void setX(float value);
            void setY(float value);
            float getX();
            float getY();
        };
    }
}

#endif