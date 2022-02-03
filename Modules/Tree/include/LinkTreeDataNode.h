#ifndef __LINK_TREE_DATA_NODE__
#define __LINK_TREE_DATA_NODE__

#include <LinkTreeNode.h>
#include <DataBag.h>

namespace DogGE{
    namespace Tree{
        template<class T>
        class LinkTreeDataNode:public LinkTreeNode, public DataBag<T>{
            public:
            LinkTreeDataNode(LinkTreeNode* parent,unsigned int id,T data);
        };
        template<class T>
        LinkTreeDataNode<T>::LinkTreeDataNode(LinkTreeNode* parent,unsigned int id,T data)
        : LinkTreeNode(parent,id), DataBag<T>(data)
        {

        }
    }
}

#endif