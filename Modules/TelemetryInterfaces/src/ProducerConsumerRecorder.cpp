#include <ProducerConsumerRecorder.h>
#include <iostream>

namespace CTelemetry{
    namespace Recorder{
        void ProducerConsumerRecorder::init(){
            this->bRun = true;
            threads[0] = std::thread(&ProducerConsumerRecorder::producer,this);
            threads[1] = std::thread(&ProducerConsumerRecorder::consumer,this);
        }
        void ProducerConsumerRecorder::close(){
            this->bRun = false;
            std::cout << "check joinable thread 1" << std::endl;
            if(threads[0].joinable()){
                std::cout << "join thread 1" << std::endl;
                threads[0].join();
            }
            std::cout << "check joinable thread 2" << std::endl;
            if(threads[1].joinable()){
                std::cout << "join thread 2" << std::endl;
                threads[1].join();
            }
            
        }
    }
}