#include <LinkTreeNode.h>

namespace DogGE{
    namespace Tree{
        LinkTreeNode::LinkTreeNode(LinkTreeNode* parent,unsigned int id)
        : AbstractTreeNode(id)
        {
            this->mParentNode = parent;
        }

        
        unsigned int LinkTreeNode::getParentId(){
            if(mParentNode != nullptr){
                return this->mParentNode->getId();
            } else {
                return 0;
            }
        }

        std::vector<unsigned int> LinkTreeNode::getChildrenIds(){
            std::vector<unsigned int> ret;
            for(auto iter:mChildrenNode){
                ret.push_back(iter->getId());
            }
            return ret;
        }

        void LinkTreeNode::addChild(LinkTreeNode* childId){
            this->mChildrenNode.push_back(childId);
        }
    }
}