#ifndef __ASSETTO_CORSA_COMPATIZIONE_RECORDER__
#define __ASSOTTO_CORSA_COMPATIZIONE_RECORDER__

#include <ProducerConsumerRecorder.h>
#include <queue>
#include <Database.h>
#include <windows.h>

namespace DogGE{
    namespace Recorder{
        class AsettoCorsaCompatizioneRecorder:public CTelemetry::Recorder::ProducerConsumerRecorder{
            protected:
            DogGE::Database::Database* mDatabase;
            std::queue<std::array<char,2000>> mQueue;
            std::mutex mtx;
            int mRecivedPackages;
            int mParsedPackages;
            
            struct SMElement{
                HANDLE hMapFile;
                unsigned char* mapFileBuffer;
            };
            SMElement mGraphics;
            SMElement mPhysics;
            SMElement mStatic;
            void initPhysics();
            void initGraphics();
            void initStatic();
            public:
            virtual void init() override;
            virtual void producer()override;
            virtual void consumer()override;
            virtual CTelemetry::Recorder::RecordState getState() override;
        };
    }
}
#endif