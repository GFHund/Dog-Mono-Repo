#ifndef __ARRAY_TREE_DATA_NODE__
#define __ARRAY_TREE_DATA_NODE__

#include <ArrayTreeNode.h>
#include <DataBag.h>

namespace DogGE{
    namespace Tree{
        template<class T>
        class ArrayTreeDataNode:public ArrayTreeNode,public DataBag<T>{
            public:
            ArrayTreeDataNode(unsigned int parentId,unsigned int id,T data);
        };
        template<class T>
        ArrayTreeDataNode<T>::ArrayTreeDataNode(unsigned int parentId,unsigned int id,T data)
        : ArrayTreeNode(parentId,id), DataBag<T>(data){

        }
    }
}

#endif 