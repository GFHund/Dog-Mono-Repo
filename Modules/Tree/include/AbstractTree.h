#ifndef __ABSTRACT_TREE__
#define __ABSTRACT_TREE__

#include <vector>

namespace DogGE {
    namespace Tree{
        template<class T>
        class AbstractTree{
            protected:
            int idCounter;
            public:
            AbstractTree();
            virtual unsigned int addNode(T newNode,unsigned int parentNodeId) = 0;
            virtual unsigned int getRootId() = 0;
            virtual T getNodeData(unsigned int id) = 0;
            virtual std::vector<T> getChildren(unsigned int id) = 0;
        };

        template<class T>
        AbstractTree<T>::AbstractTree()
        {
            idCounter = 1;
        }
    }
    
}
#endif
