#ifndef __BoundingBox2dAABB_h__
#define __BoundingBox2dAABB_h__

#include <Vector2.h>
//#include "vector2d.h"
namespace DogGE
{
	namespace Math{
		class BoundingBox2dAABB
		{
		public:
			Vector2 pos;
			Vector2 size;
			
			BoundingBox2dAABB();
			BoundingBox2dAABB(Vector2 pos,Vector2 size);
			
			bool checkCollision(BoundingBox2dAABB otherBB);
		};
	}
	
}

#endif