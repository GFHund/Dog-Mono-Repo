#include <gtest/gtest.h>
#include <iostream>
#include <sha1.h>
#include <NetworkUtility.h>
TEST(Websocket,test1){
    std::string key = "F99N6MuHl7vSdKIIv7co0g==";
    key += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    Chocobo1::SHA1 sha1;
    sha1.addData(key.c_str(),key.size());
    sha1.finalize();
    //std::string sha1Key = sha1.toString();
    auto sha1Key = sha1.toArray();
    for(int i=0;i<20;i++){
        std::cout << std::hex << int(sha1Key[i]) << std::endl;
    }
    std::string base64Key = DogGE::Network::NetworkUtility::encodeDataToBase64<20>(sha1Key);
    std::cout << base64Key << std::endl;
}