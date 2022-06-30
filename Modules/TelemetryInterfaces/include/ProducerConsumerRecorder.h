#ifndef __PRODUCER_CONSUMER_RECORDER__
#define __PROCUDER_CONSUMER_RECORDER__
#pragma once

#include <AbstractRecorderInterface.h>
#include <thread>
#include <array>

namespace CTelemetry{
    namespace Recorder{
        class ProducerConsumerRecorder:public AbstractRecorderInterface{
            protected:
            std::array<std::thread,2> threads;
            bool bRun;
            public:
            virtual void init();
            virtual void close();

            virtual void producer() = 0;
            virtual void consumer() = 0;

        };
    }
}
#endif