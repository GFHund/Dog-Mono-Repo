#include <AssettoCorsaRecorder.h>

#include <UdpClient.h>
#include <array>
#include <iostream>

namespace DogGE{
    namespace Recorder{
        void AssettoCorsaRecorder::init(){}
        void AssettoCorsaRecorder::producer(){
            DogGE::Network::UdpClient client;
            client.init("127.0.0.1","20777");
            struct handshaker{
                uint32_t identifier;
                uint32_t version;
                uint32_t operationId;
            };
            struct handshakerResponse{
                char carName[50];
                char driverName[50];
                int identifier;
                int version;
                char trackName[50];
                char trackConfig[50];
            };
            struct RTCarInfo
            {
                char identifier;//1 1
                int size;//4 5
                float speed_Kmh;//4 9
                float speed_Mph;//4 13
                float speed_Ms;// 4 17
                bool isAbsEnabled;//1 18
                bool isAbsInAction;//1 19
                bool isTcInAction;// 1 20
                bool isTcEnabled;//  1 21
                bool isInPit;//      1 22
                bool isEngineLimiterOn;//1 23
                float accG_vertical;//4 27
                float accG_horizontal;//4 31
                float accG_frontal;//4 35
                int lapTime;//       4 39
                int lastLap;//       4 43
                int bestLap;//       4 47
                int lapCount;//      4 51
                float gas;//         4 55
                float brake;//       4 59
                float clutch;//      4 63
                float engineRPM;//   4 67
                float steer;//       4 71
                int gear;//          4 75
                float cgHeight;//    4 79
                float wheelAngularSpeed[4];//4*4=16 95
                float slipAngle[4];//4*4=16 111 
                float slipAngle_ContactPatch[4];//16 127
                float slipRatio[4];//16 143
                float tyreSlip[4];// 16 159
                float ndSlip[4];
                float load[4];
                float Dy[4];
                float Mz[4];
                float tyreDirtyLevel[4];
                float camberRAD[4];
                float tyreRadius[4];
                float tyreLoadedRadius[4];
                float suspensionHeight[4];
                float carPositionNormalized;
                float carSlope;
                float carCoordinates[3];
            };
            handshaker hndshaker;
            hndshaker.identifier = 3;
            hndshaker.version = 1;
            hndshaker.operationId = 0;
            
            char* hndshakerRaw = (char*)&hndshaker;
            std::array<char,12> handshakeArray;// = std::to_array(hndshakerRaw);
            for(int i=0;i<12;i++){
                handshakeArray[i] = hndshakerRaw[i];
            }
            client.sendData<12>(handshakeArray);
            std::array<char,208> buf = client.recvData<208>();
            handshakerResponse* resp = (handshakerResponse*)buf.data();
            std::cout << resp->carName << std::endl;
            std::cout << resp->driverName << std::endl;
            std::cout << resp->trackName << std::endl;
            std::cout << resp->trackConfig  << std::endl;
            
            hndshaker.operationId = 1;
            for(int i=0;i<12;i++){
                handshakeArray[i] = hndshakerRaw[i];
            }
            client.sendData<12>(handshakeArray);

            do{
                //
            } while(this->bRun);

            hndshaker.operationId = 3;
            for(int i=0;i<12;i++){
                handshakeArray[i] = hndshakerRaw[i];
            }
            client.sendData<12>(handshakeArray);
        }
        void AssettoCorsaRecorder::consumer(){}
    }
}