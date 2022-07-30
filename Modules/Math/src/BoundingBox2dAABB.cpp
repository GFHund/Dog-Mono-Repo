#include <BoundingBox2dAABB.h>

namespace DogGE
{
	namespace Math{
		BoundingBox2dAABB::BoundingBox2dAABB()
		{
			this->pos = Vector2();
			this->size = Vector2();
		}
		BoundingBox2dAABB::BoundingBox2dAABB(Vector2 pos,Vector2 size)
		{
			this->pos = pos;
			this->size = size;
		}
			
		bool BoundingBox2dAABB::checkCollision(BoundingBox2dAABB otherBB)
		{
			bool ret = false;
			if(otherBB.pos.getX() < this->pos.getX() && otherBB.pos.getX()+otherBB.size.getX() > this->pos.getX())
			{
				if(otherBB.pos.getY() < this->pos.getY() && otherBB.pos.getY()+otherBB.size.getY() > this->pos.getY())
				{
					ret = true;
				}
				else if(otherBB.pos.getY() > this->pos.getY() && otherBB.pos.getY() < this->pos.getY() + this->size.getY())
				{
					ret = true;
				}
			}
			else if(otherBB.pos.getX() > this->pos.getX() && otherBB.pos.getX() < this->pos.getX() + this->size.getX())
			{
				if(otherBB.pos.getY() < this->pos.getY() && otherBB.pos.getY()+otherBB.size.getY() > this->pos.getY())
				{
					ret = true;
				}
				else if(otherBB.pos.getY() > this->pos.getY() && otherBB.pos.getY() < this->pos.getY() + this->size.getY())
				{
					ret = true;
				}	
			}
			return ret;
		}
	}
	
}