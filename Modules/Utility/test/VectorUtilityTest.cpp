#include <gtest/gtest.h>
#include <VectorUtility.h>

TEST(VectorUtility,mergeTest1){
    std::vector<int> arr1(4,100);
    std::vector<int> arr2(4,200);
    std::vector<int> mergedArr = (DogGE::Utility::VectorUtility<int>(arr1)).merge(arr2);
    for(int i=0;i<8;i++){
        if(i < 4){
            EXPECT_EQ(mergedArr[i],100);
        } else {
            EXPECT_EQ(mergedArr[i],200);
        }
    }
    
}