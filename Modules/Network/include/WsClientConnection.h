#ifndef __WS_CLIENT_CONNECTION__
#define __WS_CLIENT_CONNECTION__

#include <ClientConnection.h>
#include <Exceptions/ConvertWebsocketMessageException.h>
#include <stdlib.h>
#include <vector>

namespace DogGE{
    namespace Network{
        class WsClientConnection:public ClientConnection{
            public:
            template <size_t N>
            bool isString(std::array<char,N> data);
            template <size_t N>
            bool isClosingConnection(std::array<char,N> data);
            template <size_t N>
            std::string getString(std::array<char,N> data);
            template <size_t N>
            std::array<char,N> toWebsocketMessage(std::string message,bool mask = false);
        };
        template <size_t N>
        bool WsClientConnection::isString(std::array<char,N> data){
            return (data[0] & 0x01) == 0x01; 
        }
        template <size_t N>
        bool WsClientConnection::isClosingConnection(std::array<char,N> data){
            return (data[0] & 0x08) == 0x08;
        }
        template <size_t N>
        std::string WsClientConnection::getString(std::array<char,N> bytes){
            bool fin = (bytes[0] & 0x80) != 0;
            bool mask = (bytes[1] & 0x80) != 0;
            int opcode = bytes[0] & 0x0F;
            int offset = 2;
            uint64_t msglen = (uint64_t)(bytes[1] & 0x7F);
            if(msglen == 126){
                msglen = (uint64_t)bytes[3] << 8 | (uint64_t)bytes[2];
                //msglen = BitConverter.ToUInt16(new byte[]{bytes[3],bytes[2]},0);
                offset = 4;

            } else if(msglen == 127){
                //msglen = BitConverter.ToUInt64(new byte[]{bytes[9],bytes[8],bytes[7],bytes[6],bytes[5],bytes[4],bytes[3],bytes[2]},0);
                msglen = static_cast<uint64_t>(bytes[9]) << 56 | 
                static_cast<uint64_t>(bytes[8]) << 48 | 
                static_cast<uint64_t>(bytes[7]) << 40 | 
                static_cast<uint64_t>(bytes[6]) << 32 | 
                static_cast<uint64_t>(bytes[5]) << 24 |
                static_cast<uint64_t>(bytes[4]) << 16 | 
                static_cast<uint64_t>(bytes[3]) << 8  |
                static_cast<uint64_t>(bytes[2]);
                offset = 10;
            }
            if(msglen == 0){
                //Console.WriteLine("msglen == 0");
                throw ConvertWebsocketMessageException("msglen == 0");
            } else if(mask){
                char* decode = new char[msglen];
                char* masks = new char[4]; 
                //masks = bytes[offset],bytes[offset+1],bytes[offset+2],bytes[offset+3];
                offset += 4;
                for(unsigned long i = 0;i< msglen ;++i){
                    decode[i] = (char)(bytes[((unsigned long)offset) +i] ^ masks[i%4]);
                }
                std::string text = std::string(decode);
                delete[] decode;
                delete[] masks;
                //string text = Encoding.UTF8.GetString(decode);
                //Console.WriteLine(text);
                return text;
            } else {
                //Console.WriteLine("maks Bit not set");
                throw ConvertWebsocketMessageException("maks Bit not set");
            }
        }
        template <size_t N>
        std::array<char,N> WsClientConnection::toWebsocketMessage(std::string message,bool mask){
            char firstByte = 0x81;
            std::vector<char> sendingByte;
            sendingByte.push_back(firstByte);
            int messageLength = message.size();
            char secondByte = (char) messageLength;
            if(messageLength > 125 && messageLength < 0xFFFF){
                secondByte = 126;
            } else if(messageLength > 0xFFFF){
                secondByte = 127;
            }
            if(mask){
                secondByte = (char)(secondByte |0x80);
            }
            sendingByte.push_back(secondByte);
            if(secondByte == 126){
                sendingByte.push_back((char)(messageLength >> 8));
                sendingByte.push_back((char)(messageLength & 0x000F));
            } else if(secondByte == 127) {
                sendingByte.push_back((char)(messageLength >> 24));
                sendingByte.push_back((char)(messageLength >> 16));
                sendingByte.push_back((char)(messageLength >> 8));
                sendingByte.push_back((char)(messageLength & 0x000F));
            }
            char rngNumberByte[4];
            if(mask){
                int number = rand() % 0xFFFFFFFF;
                memcpy(rngNumberByte,(char*)&number,4);
                //rngNumberByte = (char*)&number;
            }
            const char* stringByteArr = message.c_str();
            for(int i=0;i<message.size();i++){
                char b = stringByteArr[i];
                if(mask){
                    b = (byte)(b ^ rngNumberByte[i%4]);
                }
                sendingByte.push_back(b);
            }
            if(sendingByte.size() > N){
                throw ConvertWebsocketMessageException("reciving Message is larger than assumed");
            }
            char* sendingByteArray = sendingByte.data();
            std::array<char,N> ret;
            memcpy(ret.data(),sendingByteArray,sendingByte.size());
            return ret;
        }
    }
}

#endif 