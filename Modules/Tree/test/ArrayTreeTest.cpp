#include <gtest/gtest.h>
#include <ArrayTree.h>
#include <Exceptions/NodeNotFoundException.h>
#include <Exceptions/NodeHasNoDataBagException.h>



TEST(ArrayTree,getRoot){
    DogGE::Tree::ArrayTree<int> tree;
    //DogGE::Tree::ArrayTree tree;
    unsigned int rootId = tree.getRootId();
    EXPECT_EQ(rootId,0);
}

TEST(ArrayTree,addAndGetNode){
    DogGE::Tree::ArrayTree<int> tree;
    unsigned int nodeId = tree.addNode(123,0);
    int treeData = tree.getNodeData(nodeId);
    EXPECT_EQ(treeData,123);
}
TEST(ArrayTree,GetNonExistentNode){
    DogGE::Tree::ArrayTree<int> tree;
    EXPECT_THROW(tree.getNodeData(123),DogGE::Tree::NodeNotFoundException);
}
TEST(ArrayTree,GetRootNode){
    DogGE::Tree::ArrayTree<int> tree;
    EXPECT_THROW(tree.getNodeData(0),DogGE::Tree::NodeHasNoDataBagException);
}