#include "AccRecorder.h"

AccRecorder::AccRecorder(){}
void AccRecorder::setOutput(std::string output){
    this->mOutput = output;
}
void AccRecorder::init(){
    mRecivedPackages = 0;
    mParsedPackages = 0;
    CTelemetry::Recorder::ProducerConsumerRecorder::init();
}
void AccRecorder::producer(){
    SMElement physics = initPhysics();
    SMElement graphics = initGraphics();

    do{
        SPageFilePhysics temp;
        SPageFilePhysics* pf = (SPageFilePhysics*)physics.mapFileBuffer;
        this->mQueue.push(temp);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } while(this->bRun);
}
void AccRecorder::consumer(){
    do{
        
    } while(this->bRun);
}
CTelemetry::REcorder::RecordState AccRecorder::getState(){}

SMElement AccRecorder::initSharedMemory(std::string sz_name){
    SMElement ret;
    ret.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), szName.c_str());
	if (!ret.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACCS", MB_OK);
	}
	ret.mapFileBuffer = (unsigned char*)MapViewOfFile(ret.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
	if (!ret.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACCS", MB_OK);
	}
    return ret;
}
SMElement AccRecorder::initPhysics(){
    return initSharedMemory("Local\\acpmf_physics");
}
SMElement AccRecorder::initGraphics(){
    return initSharedMemeory("Local\\acpmf_graphics");
}