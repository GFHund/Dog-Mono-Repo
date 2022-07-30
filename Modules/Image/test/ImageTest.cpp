#include <gtest/gtest.h>
#include <Image.h>

TEST(Image,Constructor1){
    DogGE::Image::Image img(500,500,DogGE::Image::Image::colorChannel::RGB_8BIT);
    EXPECT_EQ(img.getWidth(),500);
    EXPECT_EQ(img.getHeight(),500);
    EXPECT_EQ(img.getChannel(),DogGE::Image::Image::colorChannel::RGB_8BIT);
    int pixelsSize = img.getPixelSize();
    EXPECT_EQ(pixelsSize,500*500*3);
    uint8_t* imgRaw = img.getPixels();
    for(int i=0;i<pixelsSize;i++){
        EXPECT_EQ(imgRaw[i],0);
    }
}
TEST(Image,Constructor2){
    int arraySize = 500*500*3;
    uint8_t* imageRaw = new uint8_t[arraySize];
    DogGE::Image::Image img(imageRaw,500,500,DogGE::Image::Image::colorChannel::RGB_8BIT);
    EXPECT_EQ(img.getWidth(),500);
    EXPECT_EQ(img.getHeight(),500);
    EXPECT_EQ(img.getChannel(),DogGE::Image::Image::colorChannel::RGB_8BIT);
    int pixelsSize = img.getPixelSize();
    EXPECT_EQ(pixelsSize,500*500*3);
}