#include <Logger.h>
#include <ctime>
#include <FileOutput.h>

namespace DogGE{
    namespace Logger{
        Logger* Logger::mInstance = nullptr;

        Logger::Logger(){
            mOutput = new FileOutput("log.txt");
        }
        Logger::Logger(Logger& copy){

        }

        Logger::~Logger(){
            delete mInstance;
            delete mOutput;
        }

        Logger* Logger::getInstance(){
            if(mInstance == nullptr){
                mInstance = new Logger();
            }
            return mInstance;
        }
        void Logger::log(Logger::Severity severity,std::string message){
            time_t timer;
            time(&timer);
            struct tm* timeinfo;
            timeinfo = localtime(&timer);
            
            std::string outputMsg = "[";
            outputMsg += std::to_string(timeinfo->tm_year);
            outputMsg += "-";
            outputMsg += std::to_string(timeinfo->tm_mon);
            outputMsg += "-";
            outputMsg += std::to_string(timeinfo->tm_mday);
            outputMsg += " ";
            outputMsg += std::to_string(timeinfo->tm_hour);
            outputMsg += ":";
            outputMsg += std::to_string(timeinfo->tm_min);
            outputMsg += ":";
            outputMsg += std::to_string(timeinfo->tm_sec);
            outputMsg += "]";
            switch(severity){
                case Severity::LOGGER_NOTICE:
                    outputMsg += " NOTICE: ";
                    break;
                case Severity::LOGGER_WARNING:
                    outputMsg += " WARNING: ";
                    break;
                case Severity::LOGGER_ERROR:
                    outputMsg += " ERROR: ";
                    break;
                case Severity::LOGGER_CRITICAL:
                    outputMsg += " CRITICAL: ";
                    break;
            }
            outputMsg += message;
            this->mOutput->output(outputMsg);
        }
        void Logger::setOutput(AbstractOutput* output){
            delete this->mOutput;
        }
    }
}