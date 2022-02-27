#ifndef __LOGGER__
#define __LOGGER__

#include <string>
#include <AbstractOutput.h>
namespace DogGE{
    namespace Logger{
        class Logger{
            private:
            AbstractOutput* mOutput;
            static Logger* mInstance;

            Logger();
            Logger(Logger& copy);
            ~Logger();

            public:
            enum Severity{
                LOGGER_NOTICE,
                LOGGER_WARNING,
                LOGGER_ERROR,
                LOGGER_CRITICAL
            };
            static Logger* getInstance();
            void log(Logger::Severity severity,std::string message);
            void setOutput(AbstractOutput* output);
        };
    }
}

#endif