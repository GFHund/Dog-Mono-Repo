#include <AssettoCorsaCompatizioneRecorder.h>
#include <AssettoCorsaCompatizioneDataObjects.h>


namespace DogGE{
    namespace Recorder{

        void AsettoCorsaCompatizioneRecorder::initPhysics(){
            TCHAR szName[] = TEXT("Local\\acpmf_physics");
            mStatic.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(SPageFilePhysics),szName);
            if (!mPhysics.hMapFile){
                //Error
                //MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACCS", MB_OK);
            }
            mPhysics.mapFileBuffer = (unsigned char*)MapViewOfFile(mPhysics.hMapFile,FILE_MAP_READ,0,0,sizeof(SPageFilePhysics));
            if (!mPhysics.mapFileBuffer)
            {
                //error
                //MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACCS", MB_OK);
            }
        }
        void AsettoCorsaCompatizioneRecorder::initGraphics(){

        }
        void AsettoCorsaCompatizioneRecorder::initStatic(){

        }

        void AsettoCorsaCompatizioneRecorder::init(){
            this->initPhysics();
        }

        void AsettoCorsaCompatizioneRecorder::producer(){
            do{
                SPageFilePhysics* pf = (SPageFilePhysics*)mPhysics.mapFileBuffer;

            } while(this->bRun);
            UnmapViewOfFile(mPhysics.mapFileBuffer);
            CloseHandle(mPhysics.hMapFile);
        }
        void AsettoCorsaCompatizioneRecorder::consumer(){
            
        }
        CTelemetry::Recorder::RecordState getState(){
            return CTelemetry::Recorder::RecordState(0,0,0,0);
        }
    }
}