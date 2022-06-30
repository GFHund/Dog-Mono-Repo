#ifndef __RECORD_STATE__
#define __RECORD_STATE__
#pragma once


namespace CTelemetry{
    namespace Recorder{
        class RecordState{
            private:
            int packagesTotal;
            int packagesRead;
            int packagesWasted;
            int queueLength;
            public:
            RecordState(int packagesTotal,int packagesRead,int packagesWasted,int queueLength);

            int getTotalPackages();
            int getReadPackages();
            int getWastedPackages();
            int getQueueLength();
        };
    }
}
#endif