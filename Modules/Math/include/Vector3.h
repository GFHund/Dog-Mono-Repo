#ifndef __VECTOR_3__
#define __VECTOR_3__

#include <Vector.h>

namespace DogGE{
    namespace Math{
        class Vector3:public Vector<3>
    	{
        public:
            Vector3();
            Vector3(float x,float y,float z);
            Vector3(const Vector<3>& vector);
            void setX(float value);
            void setY(float value);
            void setZ(float value);
            void set(Vector3* vecToCopy);
            void set(Vector3 vecToCopy);
            float getX();
            float getY();
            float getZ();

            [[deprecated]]
            double getLength3();

            Vector3 crossProduct(Vector3 vector);
            Vector3 operator%(Vector3 vector);
            //bool operator==(Vector3 vector);

            static float getAngle(Vector3 a,Vector3 b);
            /*This might be unessarry*/
            static double angle(Vector3 vec1,Vector3 vec2);
            static double distance(Vector3 vecA,Vector3 vecB);
            /*This might be unessarry*/
            static double dot3(Vector3 vec1,Vector3 vec2);
            
        };
        /*This might be unessarry*/
        Vector3 operator*(double skalar,Vector3 vec);
        
    }
}

#endif