#ifndef __ABSTRACT_COMMAND__
#define __ABSTRACT_COMMAND__

namespace DogGE{
    namespace TelemetryWsServer{
        class AbstractCommand{
            public:
            enum TYPE{
                OPEN_FILE,
                DRAW_DIAGRAM,
                GET_POINTS,
                CONVERT,
                GET_CONVERT_OPTIONS,
                QUIT,
                CLOSE_FILE
            };
        };
    }
}
#endif