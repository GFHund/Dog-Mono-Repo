#include <gtest/gtest.h>
#include <HttpRequest.h>
TEST(HttpRequest,parse){
    DogGE::Network::HttpRequest request = DogGE::Network::HttpRequest::parseRequest("GET /test HTTP/1.1\r\nHost: test.com:7000\r\nUpgrade: websocket\r\nConnection: Upgrade");
    EXPECT_STREQ(request.getMethod().c_str(),"GET");
    EXPECT_STREQ(request.getEndpoint().c_str(),"/test");
    EXPECT_STREQ(request.getHttpVersion().c_str(),"HTTP/1.1");

}

TEST(HttpRequest,parseWithContent){
    DogGE::Network::HttpRequest request = DogGE::Network::HttpRequest::parseRequest("GET /test HTTP/1.1\r\nHost: test.com:7000\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n\r\nHalloWelt");
    EXPECT_STREQ(request.getMethod().c_str(),"GET");
    EXPECT_STREQ(request.getEndpoint().c_str(),"/test");
    EXPECT_STREQ(request.getHttpVersion().c_str(),"HTTP/1.1");
    EXPECT_STREQ(request.getBody().c_str(),"HalloWelt");
}