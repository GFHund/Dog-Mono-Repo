#include <Hash.h>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <string.h>

namespace DogGE{
    namespace Crypto{
         std::string Hash::sha1(std::string message){
            bool bDebug = true;

            auto circularShift = [](uint32_t word,uint32_t bits)->uint32_t{
               return (((word) << (bits)) | ((word) >> (32-(bits))));
            };
            std::ofstream ofs;
            if(bDebug){
               ofs.open("DebugHash.log",std::ofstream::out);
            }
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
               char textFragment[64];
               strncpy(textFragment,cMessage+i,64);
               if(bDebug){
                  ofs << "###############################" << std::endl;
                  ofs << "Processing Text:" << std::endl;
                  ofs << textFragment << std::endl;
                  ofs << std::hex << textFragment << std::endl;
               }
               
               uint32_t* tempBlock = (uint32_t*)(cMessage+i);
               uint32_t block[80];
               for(int j=0;j<16;j++){
                  uint8_t* blockArr = (uint8_t*) (tempBlock+j);
                  if(bDebug){
                     ofs << "------------------------------" << std::endl;
                     ofs << "Processing Block:" << std::endl;
                     ofs << "Processing Block1:";
                     ofs << blockArr[0];
                     ofs << " ";
                     ofs << std::hex << int(blockArr[0]) << std::endl;
                     ofs << "Processing Block2:";
                     ofs << blockArr[1];
                     ofs << " ";
                     ofs << std::hex << int(blockArr[1]) << std::endl;
                     ofs << "Processing Block3:";
                     ofs << blockArr[2];
                     ofs << " ";
                     ofs << std::hex << int(blockArr[2]) << std::endl;
                     ofs << "Processing Block4:";
                     ofs << blockArr[3];
                     ofs << " ";
                     ofs << std::hex << int(blockArr[3]) << std::endl;
                     ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;  
                  }
                  block[j] = blockArr[0] << 24;
                  block[j] |= blockArr[1] << 16;
                  block[j] |= blockArr[2] << 8;
                  block[j] |= blockArr[3];
                  if(bDebug){
                     ofs << "Result Block:";
                     ofs << block[j];
                     ofs << " ";
                     ofs << std::hex <<  block[j] << std::endl;
                     ofs << "------------------------------" << std::endl;
                  }
               }
               for(int j=16;j<80;j++){
                  if(bDebug){
                     ofs << "------------------------------" << std::endl;
                     ofs << "Processing Block 16-80:" << std::endl;
                     ofs << "Processing Block1:";
                     ofs << block[j - 3];
                     ofs << " ";
                     ofs << std::hex << block[j - 3] << std::endl;
                     ofs << "Processing Block2:";
                     ofs << block[j - 8];
                     ofs << " ";
                     ofs << std::hex << block[j - 8] << std::endl;
                     ofs << "Processing Block3:";
                     ofs << block[j - 14];
                     ofs << " ";
                     ofs << std::hex << block[j - 14] << std::endl;
                     ofs << "Processing Block4:";
                     ofs << block[j - 16];
                     ofs << " ";
                     ofs << std::hex << block[j - 16] << std::endl;
                     ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                  }
                  block[j] = circularShift(block[j - 3] ^ block[j - 8] ^ block[j - 14] ^ block[j - 16],1);
                  if(bDebug){
                     ofs << "Result Block:";
                     ofs << block[j];
                     ofs << " ";
                     ofs << std::hex <<  block[j] << std::endl;
                     ofs << "------------------------------" << std::endl;
                  }
               }

               if(bDebug){
                  ofs << "------------------------------" << std::endl;
                  ofs << "Set initial a-e:" << std::endl;
                  ofs << "set a:";
                  ofs << h0;
                  ofs << " ";
                  ofs << std::hex << h0 << std::endl;
                  ofs << "set b:";
                  ofs << h1;
                  ofs << " ";
                  ofs << std::hex << h1 << std::endl;
                  ofs << "set c:";
                  ofs << h2;
                  ofs << " ";
                  ofs << std::hex << h2 << std::endl;
                  ofs << "set d:";
                  ofs << h3;
                  ofs << " ";
                  ofs << std::hex << h3 << std::endl;
                  ofs << "set e:";
                  ofs << h4;
                  ofs << " ";
                  ofs << std::hex << h4 << std::endl;
                  ofs << "------------------------------" << std::endl;
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
                     if(bDebug){
                        ofs << "------------------------------" << std::endl;
                        ofs << "Set lower 20:" << std::endl;
                        ofs << "set a:";
                        ofs << a;
                        ofs << " ";
                        ofs << std::hex << a << std::endl;
                        ofs << "set b:";
                        ofs << b;
                        ofs << " ";
                        ofs << std::hex << b << std::endl;
                        ofs << "set c:";
                        ofs << c;
                        ofs << " ";
                        ofs << std::hex << c << std::endl;
                        ofs << "set d:";
                        ofs << d;
                        ofs << " ";
                        ofs << std::hex << d << std::endl;
                        ofs << "set e:";
                        ofs << e;
                        ofs << " ";
                        ofs << std::hex << e << std::endl;
                        ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                     }
                     f = (b & c) | ((~b) & d);
                     k = 0x5A827999;
                     if(bDebug){
                        ofs << "set f:";
                        ofs << f;
                        ofs << " ";
                        ofs << std::hex << f << std::endl;
                        ofs << "set k:";
                        ofs << k;
                        ofs << " ";
                        ofs << std::hex << k << std::endl;
                        ofs << "------------------------------" << std::endl;
                     }
                  }
                  else if(j >= 20 && j < 40){
                     if(bDebug){
                        ofs << "------------------------------" << std::endl;
                        ofs << "between 20 and 40:" << std::endl;
                        ofs << "set a:";
                        ofs << a;
                        ofs << " ";
                        ofs << std::hex << a << std::endl;
                        ofs << "set b:";
                        ofs << b;
                        ofs << " ";
                        ofs << std::hex << b << std::endl;
                        ofs << "set c:";
                        ofs << c;
                        ofs << " ";
                        ofs << std::hex << c << std::endl;
                        ofs << "set d:";
                        ofs << d;
                        ofs << " ";
                        ofs << std::hex << d << std::endl;
                        ofs << "set e:";
                        ofs << e;
                        ofs << " ";
                        ofs << std::hex << e << std::endl;
                        ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                     }
                     f = b ^ c ^ d;
                     k = 0x6ED9EBA1;
                     if(bDebug){
                        ofs << "set f:";
                        ofs << f;
                        ofs << " ";
                        ofs << std::hex << f << std::endl;
                        ofs << "set k:";
                        ofs << k;
                        ofs << " ";
                        ofs << std::hex << k << std::endl;
                        ofs << "------------------------------" << std::endl;
                     }
                  }
                  else if(j >= 40 && j < 60){
                     if(bDebug){
                        ofs << "------------------------------" << std::endl;
                        ofs << "between 40 and 60:" << std::endl;
                        ofs << "set a:";
                        ofs << a;
                        ofs << " ";
                        ofs << std::hex << a << std::endl;
                        ofs << "set b:";
                        ofs << b;
                        ofs << " ";
                        ofs << std::hex << b << std::endl;
                        ofs << "set c:";
                        ofs << c;
                        ofs << " ";
                        ofs << std::hex << c << std::endl;
                        ofs << "set d:";
                        ofs << d;
                        ofs << " ";
                        ofs << std::hex << d << std::endl;
                        ofs << "set e:";
                        ofs << e;
                        ofs << " ";
                        ofs << std::hex << e << std::endl;
                        ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                     }
                     f = (b & c) | (b & d) | (c & d);
                     k = 0x8F1BBCDC;
                     if(bDebug){
                        ofs << "set f:";
                        ofs << f;
                        ofs << " ";
                        ofs << std::hex << f << std::endl;
                        ofs << "set k:";
                        ofs << k;
                        ofs << " ";
                        ofs << std::hex << k << std::endl;
                        ofs << "------------------------------" << std::endl;
                     }
                  }
                  else if(j >= 60){
                     if(bDebug){
                        ofs << "------------------------------" << std::endl;
                        ofs << "above 60:" << std::endl;
                        ofs << "set a:";
                        ofs << a;
                        ofs << " ";
                        ofs << std::hex << a << std::endl;
                        ofs << "set b:";
                        ofs << b;
                        ofs << " ";
                        ofs << std::hex << b << std::endl;
                        ofs << "set c:";
                        ofs << c;
                        ofs << " ";
                        ofs << std::hex << c << std::endl;
                        ofs << "set d:";
                        ofs << d;
                        ofs << " ";
                        ofs << std::hex << d << std::endl;
                        ofs << "set e:";
                        ofs << e;
                        ofs << " ";
                        ofs << std::hex << e << std::endl;
                        ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                     }
                     f = b ^ c ^ d;
                     k = 0xCA62C1D6;
                     if(bDebug){
                        ofs << "set f:";
                        ofs << f;
                        ofs << " ";
                        ofs << std::hex << f << std::endl;
                        ofs << "set k:";
                        ofs << k;
                        ofs << " ";
                        ofs << std::hex << k << std::endl;
                        ofs << "------------------------------" << std::endl;
                     }
                  }
                  if(bDebug){
                     ofs << "------------------------------" << std::endl;
                     ofs << "set a-f + temp:" << std::endl;
                     ofs << "set block[j]:";
                     ofs << block[j];
                     ofs << " ";
                     ofs << std::hex << block[j] << std::endl;
                     ofs << "set a:";
                     ofs << a;
                     ofs << " ";
                     ofs << std::hex << a << std::endl;
                     ofs << "set b:";
                     ofs << b;
                     ofs << " ";
                     ofs << std::hex << b << std::endl;
                     ofs << "set c:";
                     ofs << c;
                     ofs << " ";
                     ofs << std::hex << c << std::endl;
                     ofs << "set d:";
                     ofs << d;
                     ofs << " ";
                     ofs << std::hex << d << std::endl;
                     ofs << "set e:";
                     ofs << e;
                     ofs << " ";
                     ofs << std::hex << e << std::endl;
                     ofs << "set f:";
                     ofs << f;
                     ofs << " ";
                     ofs << std::hex << f << std::endl;
                     ofs << "set k:";
                     ofs << k;
                     ofs << " ";
                     ofs << std::hex << k << std::endl;
                     ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                  }
                  uint32_t temp = (circularShift(a,5)) + f + e + block[j] + k;
                  e = d;
                  d = c;
                  c = circularShift(b,30);
                  b = a;
                  a = temp;
                  if(bDebug){
                     ofs << "set a:";
                     ofs << a;
                     ofs << " ";
                     ofs << std::hex << a << std::endl;
                     ofs << "set b:";
                     ofs << b;
                     ofs << " ";
                     ofs << std::hex << b << std::endl;
                     ofs << "set c:";
                     ofs << c;
                     ofs << " ";
                     ofs << std::hex << c << std::endl;
                     ofs << "set d:";
                     ofs << d;
                     ofs << " ";
                     ofs << std::hex << d << std::endl;
                     ofs << "set e:";
                     ofs << e;
                     ofs << " ";
                     ofs << std::hex << e << std::endl;
                     ofs << "set temp:";
                     ofs << temp;
                     ofs << " ";
                     ofs << std::hex << temp << std::endl;
                     ofs << "------------------------------" << std::endl;
                  }
                  
               }
               if(bDebug){
                  ofs << "------------------------------" << std::endl;
                  ofs << "set h0-h4:" << std::endl;
                  ofs << "set a:";
                  ofs << a;
                  ofs << " ";
                  ofs << std::hex << a << std::endl;
                  ofs << "set b:";
                  ofs << b;
                  ofs << " ";
                  ofs << std::hex << b << std::endl;
                  ofs << "set c:";
                  ofs << c;
                  ofs << " ";
                  ofs << std::hex << c << std::endl;
                  ofs << "set d:";
                  ofs << d;
                  ofs << " ";
                  ofs << std::hex << d << std::endl;
                  ofs << "set e:";
                  ofs << e;
                  ofs << " ";
                  ofs << std::hex << e << std::endl;

                  ofs << "set H0:";
                  ofs << h0;
                  ofs << " ";
                  ofs << std::hex << h0 << std::endl;
                  ofs << "set H1:";
                  ofs << h1;
                  ofs << " ";
                  ofs << std::hex << h1 << std::endl;
                  ofs << "set H2:";
                  ofs << h2;
                  ofs << " ";
                  ofs << std::hex << h2 << std::endl;
                  ofs << "set H3:";
                  ofs << h3;
                  ofs << " ";
                  ofs << std::hex << h3 << std::endl;
                  ofs << "set H4:";
                  ofs << h4;
                  ofs << " ";
                  ofs << std::hex << h4 << std::endl;
                  ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
               }

               h0 = h0 + a;
               h1 = h1 + b;
               h2 = h2 + c;
               h3 = h3 + d;
               h4 = h4 + e;
               if(bDebug){
                  ofs << "set H0:";
                  ofs << h0;
                  ofs << " ";
                  ofs << std::hex << h0 << std::endl;
                  ofs << "set H1:";
                  ofs << h1;
                  ofs << " ";
                  ofs << std::hex << h1 << std::endl;
                  ofs << "set H2:";
                  ofs << h2;
                  ofs << " ";
                  ofs << std::hex << h2 << std::endl;
                  ofs << "set H3:";
                  ofs << h3;
                  ofs << " ";
                  ofs << std::hex << h3 << std::endl;
                  ofs << "set H4:";
                  ofs << h4;
                  ofs << " ";
                  ofs << std::hex << h4 << std::endl;
                  ofs << "------------------------------" << std::endl;
                  ofs << "###############################"<<std::endl;
               }
            
            }
            if(bDebug){
               ofs << "------------------------------" << std::endl;
               ofs << "setup Hash:" << std::endl;
               ofs << "set H0:";
               ofs << h0;
               ofs << " ";
               ofs << std::hex << h0 << std::endl;
               ofs << "set H1:";
               ofs << h1;
               ofs << " ";
               ofs << std::hex << h1 << std::endl;
               ofs << "set H2:";
               ofs << h2;
               ofs << " ";
               ofs << std::hex << h2 << std::endl;
               ofs << "set H3:";
               ofs << h3;
               ofs << " ";
               ofs << std::hex << h3 << std::endl;
               ofs << "set H4:";
               ofs << h4;
               ofs << " ";
               ofs << std::hex << h4 << std::endl;
               ofs << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            }
            std::stringstream stream;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h0;//  << h2 << h3 << h4;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h1;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h2;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h3;
            stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << h4;
            std::string result(stream.str());
            if(bDebug){
               ofs << "set hash:";
               ofs << result;
               ofs << " ";
               ofs << std::hex << result << std::endl;
               ofs << "------------------------------" << std::endl;
               ofs << "###############################"<<std::endl;
            }
            delete[] cMessage;
            return result;
        }
    }
}