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
TEST(LinkTree,GetNonExistentNode){
    DogGE::Tree::LinkTree<int> tree;
    EXPECT_THROW(tree.getNodeData(123),DogGE::Tree::NodeNotFoundException);
}
TEST(LinkTree,GetRootNode){
    DogGE::Tree::LinkTree<int> tree;
    EXPECT_THROW(tree.getNodeData(0),DogGE::Tree::NodeHasNoDataBagException);
}
TEST(LinkTree,getChildren1){
    DogGE::Tree::LinkTree<int> tree;
    unsigned int nodeId = tree.addNode(0,0);
    unsigned int nodeId2 = tree.addNode(1,0);
    unsigned int nodeId3 = tree.addNode(2,0);
    std::vector<int> children = tree.getChildren(0);
    EXPECT_EQ(children.size(),3);
    for(int i=0;i<3;i++){
        EXPECT_EQ(children[i],i);
    }
}
TEST(LinkTree,getChildren2){
    DogGE::Tree::LinkTree<int> tree;
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
TEST(LinkTree,getChildrenException){
    DogGE::Tree::LinkTree<int> tree;
    unsigned int nodeId = tree.addNode(0,0);
    unsigned int nodeId2 = tree.addNode(1,0);
    unsigned int nodeId3 = tree.addNode(2,0);
    EXPECT_THROW(tree.getChildren(50),DogGE::Tree::NodeNotFoundException);   
}