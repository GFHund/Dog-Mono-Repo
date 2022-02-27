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

TEST(ArrayTree,getChildren1){
    DogGE::Tree::ArrayTree<int> tree;
    unsigned int nodeId = tree.addNode(0,0);
    unsigned int nodeId2 = tree.addNode(1,0);
    unsigned int nodeId3 = tree.addNode(2,0);
    std::vector<int> children = tree.getChildren(0);
    EXPECT_EQ(children.size(),3);
    for(int i=0;i<3;i++){
        EXPECT_EQ(children[i],i);
    }
}
TEST(ArrayTree,getChildren2){
    DogGE::Tree::ArrayTree<int> tree;
    unsigned int nodeId = tree.addNode(5,0);
    unsigned int nodeId2 = tree.addNode(6,0);
    unsigned int nodeId3 = tree.addNode(7,0);
    unsigned int nodeId4 = tree.addNode(0,nodeId2);
    unsigned int nodeId5 = tree.addNode(1,nodeId2);
    unsigned int nodeId6 = tree.addNode(2,nodeId2);
    unsigned int nodeId7 = tree.addNode(3,nodeId2);
    std::vector<int> children = tree.getChildren(nodeId2);
    EXPECT_EQ(children.size(),4);
    for(int i=0;i<4;i++){
        EXPECT_EQ(children[i],i);
    }
}
TEST(ArrayTree,getChildrenException){
    DogGE::Tree::ArrayTree<int> tree;
    unsigned int nodeId = tree.addNode(0,0);
    unsigned int nodeId2 = tree.addNode(1,0);
    unsigned int nodeId3 = tree.addNode(2,0);
    EXPECT_THROW(tree.getChildren(50),DogGE::Tree::NodeNotFoundException);   
}