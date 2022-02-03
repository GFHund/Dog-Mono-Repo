#ifndef __LINK_TREE_NODE__
#define __LINK_TREE_NODE__

#include <vector>
#include <AbstractTreeNode.h>

namespace DogGE{
    namespace Tree{
        
        class LinkTreeNode:public AbstractTreeNode{
            protected:
            LinkTreeNode* mParentNode;
            std::vector<LinkTreeNode*> mChildrenNode;
            public:
            LinkTreeNode(LinkTreeNode* parent,unsigned int id);
            unsigned int getParentId() override;
            std::vector<unsigned int> getChildrenIds() override;
            void addChild(LinkTreeNode* childId);
        };
    }
    
}

#endif