#ifndef __ARRAY_TREE_NODE__
#define __ARRAY_TREE_NODE__

#include <vector>
#include <AbstractTreeNode.h>

namespace DogGE{
    namespace Tree{
        
        class ArrayTreeNode:public AbstractTreeNode{
            protected:
            unsigned int mParentId;
            std::vector<unsigned int> mChildrenIds;
            public:
            ArrayTreeNode(unsigned int parentId,unsigned int id);

            unsigned int getParentId() override;
            std::vector<unsigned int> getChildrenIds() override;
            void addChild(unsigned int childId);
        };
    }
}

#endif