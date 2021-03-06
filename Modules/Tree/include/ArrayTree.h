#ifndef __ARRAY_TREE__
#define __ARRAY_TREE__

#include <vector>
#include <AbstractTree.h>
#include <ArrayTreeNode.h>
#include <ArrayTreeDataNode.h>
#include <Exceptions/NodeNotFoundException.h>
#include <Exceptions/NodeHasNoDataBagException.h>

namespace DogGE{
    namespace Tree{
        
        template<class T>
        class ArrayTree: public AbstractTree<T>{
            private:
            ArrayTreeNode* mRoot;
            std::vector<ArrayTreeDataNode<T>*> mTree;

            protected:
            ArrayTreeDataNode<T>* getTreeNodeFromId(unsigned int id);

            public:
            ArrayTree();
            ~ArrayTree();
            unsigned int addNode(T newNode,unsigned int parentNodeId) override;
            unsigned int getRootId() override;
            T getNodeData(unsigned int id);
            std::vector<T> getChildren(unsigned int parentId);
        };
       
       template<class T>
        ArrayTree<T>::ArrayTree()
        {
            mTree = std::vector<ArrayTreeDataNode<T>*>();
            mRoot = new ArrayTreeNode(0,0);
        }
        template<class T>
        ArrayTree<T>::~ArrayTree(){
            for(auto iter:mTree){
                delete iter;
            }
            delete mRoot;
        }

        template<class T>
        unsigned int ArrayTree<T>::addNode(T newNode,unsigned int parent){
            ArrayTreeDataNode<T>* treeNodeWrapper = new ArrayTreeDataNode<T>(parent,this->idCounter,newNode);
            unsigned int assignId = this->idCounter;
            this->idCounter++;
            mTree.push_back(treeNodeWrapper);
            return assignId;
        }

        template<class T>
        unsigned int ArrayTree<T>::getRootId(){
            return 0;  
        }

        template<class T>
        T ArrayTree<T>::getNodeData(unsigned int id){
            if(id == 0){
                throw NodeHasNoDataBagException();
            }
            for(auto iter:mTree){
                if(iter == nullptr){
                    continue;
                }
                if(iter->getId() == id){
                    return iter->getData();
                }
            }
            throw NodeNotFoundException();
        }
        template<class T>
        ArrayTreeDataNode<T>* ArrayTree<T>::getTreeNodeFromId(unsigned int id){
            for(auto node:mTree){
                if(node->getId() == id){
                    return node;
                }
            }
            throw NodeNotFoundException();
        }
        template<class T>
        std::vector<T> ArrayTree<T>::getChildren(unsigned int parentId){
            std::vector<T> ret;
            ArrayTreeDataNode<T>* parent = getTreeNodeFromId(parentId);
            std::vector<unsigned int> childrenIds = parent->getChildrenIds();
            for(auto childId:childrenIds){
                ArrayTreeDataNode<T>* child = getTreeNodeFromId(childId);
                ret.push_back(child->getData());
            }
            return ret;
        }
    }
     
}

#endif