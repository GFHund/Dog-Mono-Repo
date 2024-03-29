#include <F1_2022_f1_converter.h>

#include <DatabaseBuilder.h>
#include <F1DataEntity_2022.h>
#include <vector>
#include <thread>

#include <Entity/MotionPackageEntity.h>
#include <Entity/SessionPackageEntity.h>
#include <Entity/LapDataPackageEntity.h>
#include <Entity/ParticipantsPackageEntity.h>
#include <Entity/CarSetupsPackageEntity.h>
#include <Entity/CarTelemetryPackageEntity.h>
#include <Entity/CarStatusPackageEntity.h>
#include <Entity/FinalClassificationPackageEntity.h>
#include <Entity/LobbyInfoPackageEntity.h>
#include <Entity/CarDamagePackageEntity.h>
#include <Entity/SessionHistoryPackageEntity.h>


namespace DogGE{
    namespace Converters{
        bool ConverterStandardFormat::canConvert(std::string inputFile){
            
            DogGE::Database::Database* inputDatabase = DogGE::Database::DatabaseBuilder::fromFile(inputFile);
            DogGE::Database::QueryBuilder queryBuilder = inputDatabase->createQueryBuilder("F1DataEntity");
            queryBuilder.setLimit(1);
            std::vector<DogGE::F1_2022::F1DataEntity*> result = inputDatabase->selectAllData<DogGE::F1_2022::F1DataEntity>(queryBuilder);
            delete inputDatabase;
            return result[0]->getPacketFormat() == 2022;
        }
        void ConverterStandardFormat::convert(std::string input,std::string output){
            DogGE::Database::Database* inputFileDatabase = DogGE::Database::DatabaseBuilder::fromFile(input);
            DogGE::Database::Database* inputDatabase = DogGE::Database::DatabaseBuilder::convertFileIntoMemory(inputFileDatabase);
            DogGE::Database::Database* outputDatabase = DogGE::Database::DatabaseBuilder::fromMemory();
            DogGE::Database::QueryBuilder queryBuilder = inputDatabase->createQueryBuilder("F1DataEntity");
            queryBuilder.addGroupBy("sessionUID");
            queryBuilder.addGroupBy("frameIdentifier");
            queryBuilder.addOrderBy("sessionUID");
            queryBuilder.addOrderBy("frameIdentifier");
            int amount = inputDatabase->countData(queryBuilder);
            std::vector<std::thread> threads;

            for(int i=0;i<amount;i+=1000){
                for(int j=0;j<10;j++){
                    //threads.push_back(std::thread(&ConverterStandardFormat::insertDataPoint,inputDatabase,outputDatabase,i+j*100));
                }
                
            }

            DogGE::Database::Database* outputFileDatabase = DogGE::Database::DatabaseBuilder::convertMemoryIntoFile(outputDatabase,output);
            delete outputFileDatabase;
            delete inputFileDatabase;
            delete inputDatabase;
            delete outputDatabase;

        }
        void ConverterStandardFormat::insertDataPoint(DogGE::Database::Database* input,DogGE::Database::Database* output,int offset){
            DogGE::Database::QueryBuilder queryBuilder = input->createQueryBuilder("F1DataEntity");
            queryBuilder.addGroupBy("sessionUID");
            queryBuilder.addGroupBy("frameIdentifier");
            queryBuilder.addOrderBy("sessionUID");
            queryBuilder.addOrderBy("frameIdentifier");
            queryBuilder.setLimit(100,offset);
            std::string dataPointsSql = "SELECT sessionUID,frameIdentifier FROM F1DataEntity GROUP BY sessionUID,frameIdentifier ORDER BY sessionUID,frameIdentifier LIMIT 100,"+std::to_string(offset);
            DogGE::Database::PrepareStatement* datapointStmt = input->prepareStatement(dataPointsSql);
            std::string packagesSQL = "SELECT packet,packetId FROM F1DataEntity WHERE sessionUID = @session AND frameIdentifier = @frame";
            DogGE::Database::PrepareStatement* packagesStmt = input->prepareStatement(packagesSQL);
            while(datapointStmt->fetch()){
                uint64_t sessionUID = datapointStmt->readInt64Value(0);
                uint8_t frameIdentifier = datapointStmt->readIntValue(1);
                
                packagesStmt->setInt64Param(1,sessionUID);
                packagesStmt->setIntParam(2,frameIdentifier);
                while(packagesStmt->fetch()){
                    uint8_t packetId = datapointStmt->readIntValue(1);
                    int size=0;
                    std::array<char,2000> data = datapointStmt->readBlob<2000>(0,&size);
                    switch(packetId){
                        case 0:{
                            DogGE::F1_2022::MotionPackageEntity(data.data(),1464);
                            break;
                        }
                        case 1:{
                            DogGE::F1_2022::SessionPackageEntity(data.data(),632);
                            break;
                        }
                        case 2:{
                            DogGE::F1_2022::LapDataPackageEntity(data.data(),972);
                            break;
                        }
                        case 4:{
                            DogGE::F1_2022::ParticipantsPackageEntity(data.data(),1257);
                            break;
                        }
                        case 5:{
                            DogGE::F1_2022::CarSetupsPackageEntity(data.data(),1102);
                            break;
                        }
                        case 6:{
                            DogGE::F1_2022::CarTelemetryPackageEntity(data.data(),1347);
                            break;
                        }
                        case 7:{
                            DogGE::F1_2022::CarStatusPackageEntity(data.data(),1058);
                            break;
                        }
                        case 8:{
                            DogGE::F1_2022::FinalClassificationPackageEntity(data.data(),1015);
                            break;
                        }
                        case 9:{
                            DogGE::F1_2022::LobbyInfoPackageEntity(data.data(),1191);
                            break;
                        }
                        case 10:{
                            DogGE::F1_2022::CarDamagePackageEntity(data.data(),948);
                            break;
                        }
                        case 11:{
                            DogGE::F1_2022::SessionHistoryPackageEntity(data.data(),1155);
                            break;
                        }
                    }

                }
                packagesStmt->resetParam();
            }
            delete packagesStmt;
            delete datapointStmt;
        }
    }
}                                                                    