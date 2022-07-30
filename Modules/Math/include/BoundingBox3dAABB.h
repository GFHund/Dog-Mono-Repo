#ifndef __boundingBox3dAABB_h__
#define __boundingBox3dAABB_h__
#include "Vector3.h"
namespace DogGE
{
	namespace Math{
		class BoundingBox3dAABB
		{
			Vector3 pos;
			Vector3 size;
		public:
			BoundingBox3dAABB();
			BoundingBox3dAABB(Vector3 pos,Vector3 size);
			//CBoundingBox3dAABB(CVector3d min,CVector3d max);

			Vector3 getPos();
			Vector3 getSize();
			Vector3 getMax();

			void translate(Vector3 translateVec);
			bool checkCollision(BoundingBox3dAABB otherBB);
		};
	}
};
#endif
