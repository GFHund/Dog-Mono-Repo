#ifndef __ACC_RECORDER__
#define __ACC_RECORDER__

#include <queue>
#include <mutex>
#include <Database.h>
#include <ProducerConsumerRecorder.h>
#include <RecordState.h>
#include "ACC/SharedFileOut.h"

class AccRecorder:public CTelemetry::Recorder::ProducerConsumerRecorder{
    protected:
    DogGE::Database::Database* mDatabase;
    std::queue<std::array<char,2000>> mQueue;
    std::mutex mtx;
    int mRecivedPackages;
    int mParsedPackages;
    std::string mOutput;

    SMElement initSharedMemory(std::string sz_name);
    SMElement initPhysics();
    SMElement initGraphics();

    public:
        AccRecorder();
        void setOutput(std::string output);
        virtual void init() override;
        virtual void producer() override;
        virtual void consumer() override;
        virtual CTelemetry::REcorder::RecordState getState() override
};

#endif