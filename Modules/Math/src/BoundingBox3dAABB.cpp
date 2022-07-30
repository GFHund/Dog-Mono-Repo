#include <BoundingBox3dAABB.h>
namespace DogGE
{
	namespace Math{

		BoundingBox3dAABB::BoundingBox3dAABB()
		{
			this->pos = Vector3();
			this->size = Vector3();
		}
		//------------------------------------------------------------------
		BoundingBox3dAABB::BoundingBox3dAABB(Vector3 pos,Vector3 size)
		{
			this->pos = pos;
			this->size = size;
		}
		//------------------------------------------------------------------
		/*
		CBoundingBox3dAABB::CBoundingBox3dAABB(CVector3d min,CVector3d max)
		{
			//aaa
		}
		*/
		//------------------------------------------------------------------
		/*Get the minimum Pos*/
		Vector3 BoundingBox3dAABB::getPos()
		{
			return this->pos;
		}
		//------------------------------------------------------------------
		/*get the size of the Bounding Box*/
		Vector3 BoundingBox3dAABB::getSize()
		{
			return this->size;
		}
		//------------------------------------------------------------------
		/*get the maximum Pos*/
		Vector3 BoundingBox3dAABB::getMax()
		{
			return this->pos + this->size;
		}
		//------------------------------------------------------------------
		void BoundingBox3dAABB::translate(Vector3 translateVec)
		{
			this->pos = this->pos + translateVec;
		}
		//------------------------------------------------------------------
		bool BoundingBox3dAABB::checkCollision(BoundingBox3dAABB otherBB)
		{
			Vector3 amin = this->getPos();
			Vector3 amax = this->getMax();
			Vector3 bmin = otherBB.getPos();
			Vector3 bmax = otherBB.getMax();

			return (amin.getX() <= bmax.getX() && amax.getX() >= bmin.getX() &&
				amin.getY() <= bmax.getY() && amax.getY() >= bmin.getY() &&
				amin.getZ() <= bmax.getZ() && amax.getZ() >= bmin.getZ());
			/*
			CVector3d diff = getPos() - otherBB.getPos();
			bool x = false;
			bool y = false;
			bool z = false;
			if (diff.getX() > 0)
			{
				if (otherBB.getSize().getX() > diff.getX())
				{
					x = true;
				}
			}
			else
			{
				if (getSize().getX() > diff.getX())
				{
					x = true;
				}
			}
			if (diff.getY() > 0)
			{
				if (otherBB.getSize().getY() > diff.getY())
				{
					y = true;
				}
			}
			else
			{
				if (getSize().getY() > diff.getY())
				{
					y = true;
				}
			}
			if (diff.getZ() > 0)
			{
				if (otherBB.getSize().getZ() > diff.getZ())
				{
					z = true;
				}
			}
			else
			{
				if (getSize().getZ() > diff.getZ())
				{
					z = true;
				}
			}
			return x && y && z;
			*/
			/*
			bool ret[6];
			for(int i=0;i<6;i++)
			{
				ret[i] = false;
			}
			//Higher Point from otherBB
			CVector3d higherPoint = this->pos + this->size;
			CVector3d higherPointOBB = this->getMax();//otherBB.pos + otherBB.size;
			//pos.x liegt innerhalb von otherBB
			if(otherBB.pos.getX() < this->pos.getX() && higherPointOBB.getX() > this->pos.getX() )
			{
				ret[0] = true;
			}
			if(otherBB.pos.getX() > this->pos.getX() && otherBB.pos.getX() < higherPoint.getX() )
			{
				ret[1]=true;
			}

			if(otherBB.pos.getY() < this->pos.getY() && higherPointOBB.getY() > this->pos.getY() )
			{
				ret[2] = true;
			}
			if(otherBB.pos.getY() > this->pos.getY() && otherBB.pos.getY() < higherPoint.getY() )
			{
				ret[3]=true;
			}

			if(otherBB.pos.getZ() < this->pos.getZ() && higherPointOBB.getZ() > this->pos.getZ() )
			{
				ret[4] = true;
			}
			if(otherBB.pos.getZ() > this->pos.getZ() && otherBB.pos.getZ() < higherPoint.getZ() )
			{
				ret[5]=true;
			}

			return (ret[0] || ret[1]) && (ret[2] || ret[3]) && (ret[4] || ret[5]);
			*/
			/*
			bool ret = false;
			if(otherBB.pos.x < this->pos.x && otherBB.pos.x+otherBB.size.x > this->pos.x)
			{
				if(otherBB.pos.y < this->pos.y && otherBB.pos.y+otherBB.size.y > this->pos.y)
				{
					ret = true;
				}
				else if(otherBB.pos.y > this->pos.y && otherBB.pos.y < this->pos.y + this->size.y)
				{
					ret = true;
				}
			}
			else if(otherBB.pos.x > this->pos.x && otherBB.pos.x < this->pos.x + this->size.x)
			{
				if(otherBB.pos.y < this->pos.y && otherBB.pos.y+otherBB.size.y > this->pos.y)
				{
					ret = true;
				}
				else if(otherBB.pos.y > this->pos.y && otherBB.pos.y < this->pos.y + this->size.y)
				{
					ret = true;
				}
			}
			return ret;
			*/
		}

	}
	
}
