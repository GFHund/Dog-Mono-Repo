#include <gtest/gtest.h>
#include <LinkTree.h>

TEST(LinkTree,getRoot){
    DogGE::Tree::LinkTree<int> tree;
    //DogGE::Tree::ArrayTree tree;
    unsigned int rootId = tree.getRootId();
    EXPECT_EQ(rootId,0);
}

TEST(LinkTree,addAndGetNode){
    DogGE::Tree::LinkTree<int> tree;
    unsigned int nodeId = tree.addNode(123,0);
    int treeData = tree.getNodeData(nodeId);
    EXPECT_EQ(treeData,123);
}