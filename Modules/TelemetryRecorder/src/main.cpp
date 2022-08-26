#include <iostream>
#include <windows.h>
#include "../vendor/cxxopts/cxxopts.hpp"
#include <ProducerConsumerRecorder.h>
#include <Recorder_2021.h>
#include <Recorder_2022.h>

bool bCloseProgram;

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType){
    if(fdwCtrlType == CTRL_C_EVENT){
        std::cout << "Exit Program" << std::endl;
        bCloseProgram = true;
        return true;
    }
    return false;
}

int main(int argc,char** argv){
    bCloseProgram = false;
    if(!SetConsoleCtrlHandler(CtrlHandler,TRUE)){
        std::cout << "Could not create ctrl handle function" << std::endl;
        return 1;
    }
    cxxopts::Options options("F1GameParserGenerator",
    "Generate Sources for parsing and recording of a Codemaster F1 Game");
    options.add_options()
    ("g,game","Specifies the Recorded Game",cxxopts::value<std::string>())
    ("o,output","Specifies the dir name which the generated sources will be put into",cxxopts::value<std::string>())
    ("h,help","get this Help Test");
    auto result = options.parse(argc,argv);
    if(result.count("help")){
        std::cout << options.help() << std::endl;
        exit(0);
    }
    std::string game = result["game"].as<std::string>();
    std::string output = result["output"].as<std::string>();

    CTelemetry::Recorder::ProducerConsumerRecorder* recorder = nullptr;

    if(game.compare("2021") == 0 || game.compare("F1_2021") == 0){
        recorder = new DogGE::F1_2021::Recorder_2021();
        ((DogGE::F1_2021::Recorder_2021*)recorder)->setOutput(output);
    } else if(game.compare("2022") == 0 || game.compare("F1_2022") == 0){
        recorder = new DogGE::F1_2022::Recorder_2022();
        ((DogGE::F1_2022::Recorder_2022*) recorder)->setOutput(output);
    } else {
        std::cout << "game Not FOund" << std::endl;
        return 0;
    }

    recorder->init();
    std::cout << bCloseProgram << std::endl;
    while(!bCloseProgram){
        std::this_thread::sleep_for(std::chrono::seconds(10));
        CTelemetry::Recorder::RecordState state = recorder->getState();
        std::cout << "Recived Packages: "<< state.getTotalPackages() << " Parsed Packages: " << state.getReadPackages() << " Discaded Packages: " << state.getWastedPackages() << " Queue Length: " << state.getQueueLength() <<std::endl;
    }
    std::cout << "close Recorder" << std::endl;
    recorder->close();
    
    delete recorder;
    return 0;
}