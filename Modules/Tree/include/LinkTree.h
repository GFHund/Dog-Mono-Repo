#ifndef __LINK_TREE__
#define __LINK_TREE__

#include <vector>
#include <AbstractTree.h>
#include <LinkTreeNode.h>
#include <LinkTreeDataNode.h>
#include <Exceptions/NodeNotFoundException.h>
#include <Exceptions/NodeHasNoDataBagException.h>

namespace DogGE{
    namespace Tree{
        template<typename Base, typename T>
        inline bool instanceof(const T *ptr) {
            return dynamic_cast<const Base*>(ptr) != nullptr;
        }
        template<class T>
        class LinkTree:public AbstractTree<T>{
            private:
            LinkTreeNode* mRoot;
            std::vector<LinkTreeDataNode<T>*> mTree;
            protected:
            LinkTreeDataNode<T>* getTreeNodeFromId(unsigned int id);
            public:
            LinkTree();
            ~LinkTree();
            unsigned int addNode(T newNode,unsigned int parentNodeId) override;
            unsigned int getRootId() override;
            T getNodeData(unsigned int id);
            std::vector<T> getChildren(unsigned int id) override;
        };

        template<class T>
        LinkTree<T>::LinkTree(){
            mTree = std::vector<LinkTreeDataNode<T>*>();
            mRoot = new LinkTreeNode(0,0);
        }

        template<class T>
        LinkTree<T>::~LinkTree(){
            for(auto iter:mTree){
                delete iter;
            }
            delete mRoot;
        }
        template<class T>
        unsigned int LinkTree<T>::addNode(T data, unsigned int parentNodeId){
            unsigned int assignId = this->idCounter;
            if(parentNodeId == 0){
                LinkTreeDataNode<T>* newNode = new LinkTreeDataNode<T>(mRoot,assignId,data);
                this->mTree.push_back(newNode);
            } else {
                try{
                    LinkTreeDataNode<T>* parentNode = getTreeNodeFromId(parentNodeId);
                    LinkTreeDataNode<T>* newNode = new LinkTreeDataNode<T>(parentNode,assignId,data);
                    this->mTree.push_back(newNode);
                } catch(NodeNotFoundException &e){
                    throw e;
                }
                
            }
            this->idCounter++;
            return assignId;
        }
        template<class T>
        LinkTreeDataNode<T>* LinkTree<T>::getTreeNodeFromId(unsigned int id){
            for(auto iter:mTree){
                if(iter == nullptr){
                    continue;
                }
                if(iter->getId() == id){
                    return iter;
                }
            }
            throw NodeNotFoundException();
        }

        template<class T>
        unsigned int LinkTree<T>::getRootId(){
            return 0;
        }

        template<class T>
        T LinkTree<T>::getNodeData(unsigned int id){
            if(id == 0){
                throw NodeHasNoDataBagException();
            }
            LinkTreeDataNode<T>* node = this->getTreeNodeFromId(id);
            return node->getData();
            
        }

        template<class T>
        std::vector<T> LinkTree<T>::getChildren(unsigned int id){
            std::vector<T> ret;
            LinkTreeDataNode<T>* parent = getTreeNodeFromId(id);
            std::vector<unsigned int> childrenIds = parent->getChildrenIds();
            for(auto childId:childrenIds){
                LinkTreeDataNode<T>* child = getTreeNodeFromId(childId);
                ret.push_back(child->getData());
            }
            return ret;
        }
    }
    
}

#endif