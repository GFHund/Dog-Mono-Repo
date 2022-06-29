#include <{{&HEADER_FILE}}>

namespace DogGE{
    namespace {{&NAMESPACE_NAME}}{
        bool {{&CLASS_NAME}}::canConvert(std::string inputFile){
            
            DogGE::Database::Database* inputDatabase = DogGE::Database::DatabaseBuilder::fromFile(inputFile);
            DogGE::Database::QueryBuilder queryBuilder = inputDatabase->createQueryBuilder("{{&DB_TABLE}}");
            queryBuilder.setLimit(1);
            std::vector<{{&ENTITY_CLASS}}> result = inputDatabase->selectAllData<{{&ENTITY_CLASS}}>(queryBuilder);
            delete inputDatabase;
            return result[0]->getPacketFormat() == {{&PACKET_FORMAT}};
        }
        void {{&CLASS_NAME}}::convert(std::string input,std::string output){
            DogGE::Database::Database* inputFileDatabase = DogGE::Database::DatabaseBuilder::fromFile(inputFile);
            DogGE::Database::Database* inputDatabase = DogGE::Database::DatabaseBuilder::convertFileIntoMemory(inputFileDatabase);
            DogGE::Database::Database* outputDatabase = DogGE::Database::DatabaseBuilder::fromMemory();
            DogGE::Database::QueryBuilder queryBuilder = inputDatabase->createQueryBuilder("{{&DB_TABLE}}");
            queryBuilder.addGroupBy("sessionUID");
            queryBuilder.addGroupBy("frameIdentifier");
            queryBuilder.addOrderBy("sessionUID");
            queryBuilder.addOrderBy("frameIdentifier");
            int amount = inputDatabase->countData(queryBuilder);
            std::vector<std::thread> threads;

            for(int i=0;i<amount;i+=1000){
                for(int j=0;j<10;j++){
                    threads.push_back(&{{&CLASS_NAME}}::insertDataPoint,inputDatabase,outputDatabase,i+j*100);
                }
                
            }

            DogGE::Database::Database* outputFileDatabase = DogGE::Database::DatabaseBuilder::convertMemoryIntoFile(outputDatabase,output);
            delete outputFileDatabase;
            delete inputFileDatabase;
            delete inputDatabase;
            delete outputDatabase;

        }
        void {{&CLASS_NAME}}::insertDataPoint(DogGE::Database::Database* input,DogGE::Database::Database* output,int offset){
            DogGE::Database::QueryBuilder queryBuilder = inputDatabase->createQueryBuilder("{{&DB_TABLE}}");
            queryBuilder.addGroupBy("sessionUID");
            queryBuilder.addGroupBy("frameIdentifier");
            queryBuilder.addOrderBy("sessionUID");
            queryBuilder.addOrderBy("frameIdentifier");
            queryBuilder.addLimit(100,offset);
            std::string dataPointsSql = "SELECT sessionUID,frameIdentifier FROM {{&DB_TABLE}} GROUP BY sessionUID,frameIdentifier ORDER BY sessionUID,frameIdentifier LIMIT 100,"+std::to_string(offset);
            DogGE::Database::PrepareStatement* datapointStmt = input->prepareStatement(dataPointsSql);
            std::string packagesSQL = "SELECT packet,packetId FROM {{&DB_TABLE}} WHERE sessionUID = @session AND frameIdentifier = @frame";
            DogGE::Database::PrepareStatement* packagesStmt = input->prepareStatement(packagesSQL);
            while(datapointStmt->fetch()){
                uint64_t sessionUID = datapointStmt->readInt64Value(0);
                uint8_t frameIdentifier = datapointStmt->readIntValue(1);
                
                packagesStmt->setInt64Param(1,sessionUID);
                packagesStmt->setIntParam(2,frameIdentifier);
                while(packagesStmt->fetch()){
                    uint8_t packetId = datapointStmt->readIntValue(1);
                    int size=0;
                    std::array<char,2000> data = datapointStmt->readBlobValue<2000>(0,&size);
                    {{&SELECT_PACKAGES}}
                }
                packagesStmt->resetParam();
            }
            delete packagesStmt;
            delete datapointStmt;
        }
    }
}