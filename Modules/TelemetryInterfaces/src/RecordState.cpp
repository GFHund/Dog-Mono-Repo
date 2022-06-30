#include <RecordState.h>

namespace CTelemetry{
    namespace Recorder{
        RecordState::RecordState(int packagesTotal,int packagesRead,int packagesWasted,int queueLength){
            this->packagesTotal = packagesTotal;
            this->packagesRead = packagesRead;
            this->packagesWasted = packagesWasted;
            this->queueLength = queueLength;
        }

        int RecordState::getTotalPackages(){
            return this->packagesTotal;
        }
        int RecordState::getReadPackages(){
            return this->packagesRead;
        }
        int RecordState::getWastedPackages(){
            return this->packagesWasted;
        }
        int RecordState::getQueueLength(){
            return this->queueLength;
        }
    }
}