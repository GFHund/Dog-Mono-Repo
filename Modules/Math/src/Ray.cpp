#include <Ray.h>
namespace DogGE
{
  namespace Math{
    Ray::Ray(Vector3 origin,Vector3 direction)
    {
      this->mOrigin = origin;
      this->mDirection = direction;
    }

    Vector3 Ray::getOrigin()
    {
      return this->mOrigin;
    }
    Vector3 Ray::getDirection()
    {
      return this->mDirection;
    }
    Vector3 Ray::getPos(float lambda)
    {
      return this->mOrigin + this->mDirection * lambda;
    }

    bool Ray::checkCollision(BoundingBox3dAABB bb,float& lambdaMin,float& lambdaMax)
    {
      float dirX = 1.0f / this->mDirection.getX();
      float dirY = 1.0f / this->mDirection.getY();
      float dirZ = 1.0f / this->mDirection.getZ();
      Vector3 bbMin = bb.getPos();
      Vector3 bbMax = bb.getMax();
      float tx1 = (bbMin.getX() - this->mOrigin.getX())*dirX;
      float tx2 = (bbMax.getX() - this->mOrigin.getX())*dirX;
      float ty1 = (bbMin.getY() - this->mOrigin.getY())*dirY;
      float ty2 = (bbMax.getY() - this->mOrigin.getY())*dirY;
      float tz1 = (bbMin.getZ() - this->mOrigin.getZ())*dirZ;
      float tz2 = (bbMax.getZ() - this->mOrigin.getZ())*dirZ;
      float tMin,tMax;
      if(tx1 > ty2 || ty1 > tx2)
      {
        return false;
      }
      if(ty1 > tx1)
      {
        tMin = ty1;
      }
      else
      {
        tMin = tx1;
      }
      if(ty2 < tx2)
      {
        tMax = ty2;
      }
      else
      {
        tMax = tx2;
      }

      if(tMin > tz2 || tz1 > tMax)
      {
        return false;
      }
      if(tz1 > tMin)
      {
        tMin = tz1;
      }
      if(tz2 < tMax)
      {
        tMax = tz2;
      }
      lambdaMin = tMin;
      lambdaMax = tMax;
      return true;
    }
  }
}
