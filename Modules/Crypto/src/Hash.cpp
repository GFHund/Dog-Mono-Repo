#include <Hash.h>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <iomanip>

namespace DogGE{
    namespace Crypto{
         std::string Hash::sha1(std::string message){
            auto circularShift = [](uint32_t word,uint32_t bits)->uint32_t{
               return (((word) << (bits)) | ((word) >> (32-(bits))));
            };
            
            /*
            uint32_t test = 4;
            for(int i=0;i<64;i++){
               printf("vor: %02X %d\n",test,test);
               test = circularShift(test,1);
               printf("danach: %02X %d\n",test,test);
            }
            */
            
            uint32_t h0 = 0x67452301;
            uint32_t h1 = 0xEFCDAB89;
            uint32_t h2 = 0x98BADCFE;
            uint32_t h3 = 0x10325476;
            uint32_t h4 = 0xC3D2E1F0;

            uint64_t messageLengthInBits = message.size() * 8;
            uint64_t lengthLastBlock = messageLengthInBits % 512;
            uint64_t charLength = (messageLengthInBits + (512 - lengthLastBlock)) / 8;
            char* cMessage = new char[charLength];
            for(int i=0;i<charLength;i++){
               cMessage[i] = 0x0;
            }
            for(int i = 0;i<message.size();i++){
               cMessage[i] = message[i];
            }
            
            cMessage[message.size()] = (char)0x80;//pad a 1 on the end of the message
            
            for(int i = lengthLastBlock+8;i<448;i+=8){
               int index = charLength - (512 - i) / 8;
               cMessage[index]  = 0x00;
               //message += (char)0x00;
            }
            char* cMessageLengthBits = (char*)&messageLengthInBits;
            cMessage[charLength-1] = cMessageLengthBits[0];
            cMessage[charLength-2] = cMessageLengthBits[1];
            cMessage[charLength-3] = cMessageLengthBits[2];
            cMessage[charLength-4] = cMessageLengthBits[3];

            cMessage[charLength-4] = cMessageLengthBits[4];
            cMessage[charLength-5] = cMessageLengthBits[5];
            cMessage[charLength-6] = cMessageLengthBits[6];
            cMessage[charLength-7] = cMessageLengthBits[7];
            
            for(int i = 0;i<charLength;i+=64){
               uint32_t* tempBlock = (uint32_t*)(cMessage+i);
               uint32_t block[80];
               for(int j=0;j<16;j++){
                  uint8_t* blockArr = (uint8_t*) (tempBlock+j);
                  block[j] = blockArr[0] << 24;
                  block[j] |= blockArr[1] << 16;
                  block[j] |= blockArr[2] << 8;
                  block[j] |= blockArr[3];
                  
               }
               for(int j=16;j<80;j++){
                  block[j] = circularShift(block[j - 3] ^ block[j - 8] ^ block[j - 14] ^ block[j - 16],1);
                  
               }

               uint32_t a = h0;
               uint32_t b = h1;
               uint32_t c = h2;
               uint32_t d = h3;
               uint32_t e = h4;
               
               for(int j = 0;j<80;j++){
                  uint32_t f = 0;
                  uint32_t k = 0;
                  if(j < 20){
                     f = (b & c) | ((~b) & d);
                     k = 0x5A827999;
                  }
                  else if(j >= 20 && j < 40){
                     f = b ^ c ^ d;
                     k = 0x6ED9EBA1;
                  }
                  else if(j >= 40 && j < 60){
                     f = (b & c) | (b & d) | (c & d);
                     k = 0x8F1BBCDC;
                  }
                  else if(j >= 60){
                     f = b ^ c ^ d;
                     k = 0xCA62C1D6;
                  }
                  
                  printf("t: %d\n",j);
                  printf("W[t]: %02X\n",block[j]);
                  printf("A: %02X\n",a);
                  printf("B: %02X\n",b);
                  printf("C: %02X\n",c);
                  printf("D: %02X\n",d);
                  printf("E: %02X\n\n",e);

                  uint32_t temp = (circularShift(a,5)) + f + e + block[j] + k;
                  e = d;
                  d = c;
                  c = circularShift(b,30);
                  b = a;
                  a = temp;
  
                  
               }

               printf("A: %02X\n",a);
               printf("B: %02X\n",b);
               printf("C: %02X\n",c);
               printf("D: %02X\n",d);
               printf("E: %02X\n\n",e);

               h0 = h0 + a;
               h1 = h1 + b;
               h2 = h2 + c;
               h3 = h3 + d;
               h4 = h4 + e;

            }
            printf("h1: %02X\n",h0);
            printf("h2: %02X\n",h1);
            printf("h3: %02X\n",h2);
            printf("h4: %02X\n",h3);
            printf("h5: %02X\n\n",h4);
            std::stringstream stream;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h0;//  << h2 << h3 << h4;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h1;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h2;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h3;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h4;
            std::string result(stream.str());
            delete[] cMessage;
            return result;
        }
    }
}