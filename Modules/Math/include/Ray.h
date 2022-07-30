#include <Vector3.h>
#include <BoundingBox3dAABB.h>

namespace DogGE
{
  namespace Math{
    class Ray
    {
    private:
      Vector3 mOrigin;
      Vector3 mDirection;
    public:
      Ray(Vector3 origin,Vector3 direction);
      Vector3 getOrigin();
      Vector3 getDirection();
      Vector3 getPos(float lambda);
      bool checkCollision(BoundingBox3dAABB bb,float& lambdaMin,float& lambdaMax);
    };
  }
  
}
