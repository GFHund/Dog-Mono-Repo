#ifndef __ABSTRACT_TREE_NODE__
#define __ABSTRACT_TREE_NODE__

#include <vector>

namespace DogGE{
    namespace Tree{
        class AbstractTreeNode{
            protected:
            unsigned int mId;
            

            public:
            AbstractTreeNode(unsigned int id);
            
            unsigned int getId();
            virtual unsigned int getParentId() = 0;
            virtual std::vector<unsigned int> getChildrenIds() = 0;
            
        };
    }
    
}

#endif