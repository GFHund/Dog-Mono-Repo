#include <ArrayTreeNode.h>

namespace DogGE{
    namespace Tree{
        ArrayTreeNode::ArrayTreeNode(unsigned int parentId,unsigned int id)
        : AbstractTreeNode(id)
        {
            this->mParentId = parentId;
        }
        
        
        unsigned int ArrayTreeNode::getParentId(){
            return this->mParentId;
        }

        
        std::vector<unsigned int> ArrayTreeNode::getChildrenIds(){
            return this->mChildrenIds;   
        }

        
        void ArrayTreeNode::addChild(unsigned int childId){
            this->mChildrenIds.push_back(childId);
        }
    }
}