#include <AbstractTreeNode.h>

namespace DogGE{
    namespace Tree{
        AbstractTreeNode::AbstractTreeNode(unsigned int id){
            this->mId = id;
            
        }

        unsigned int AbstractTreeNode::getId(){
            return this->mId;
        }
    }
}