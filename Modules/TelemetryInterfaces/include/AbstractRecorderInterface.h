#ifndef __ABSTRACT_RECORDER_INTERFACE__
#define __ABSTRACT_RECORDER_INTERFACE__
#pragma once

#include <RecordState.h>

namespace CTelemetry{
    namespace Recorder{
        class AbstractRecorderInterface{
            private:
            int packagesTotal;
            int packagesRead;
            public:
            virtual void init() = 0;
            virtual void close() = 0;
            virtual RecordState getState() = 0;
        };
    }
}
#endif