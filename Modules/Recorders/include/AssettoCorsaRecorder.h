#ifndef __ASSETTO_CORSA__
#define __ASSETTO_CORSA__

#include <ProducerConsumerRecorder.h>
#include <queue>
#include <Database.h>

namespace DogGE{
    namespace Recorder{
        class AssettoCorsaRecorder:public CTelemetry::Recorder::ProducerConsumerRecorder{
            protected:
            DogGE::Database::Database* mDatabase;
            std::queue<std::array<char,2000>> mQueue;
            std::mutex mtx;
            int mRecivedPackages;
            int mParsedPackages;
            public:
            virtual void init() override;
            virtual void producer()override;
            virtual void consumer()override;
            virtual CTelemetry::Recorder::RecordState getState() override;
        };
    }
}
#endif