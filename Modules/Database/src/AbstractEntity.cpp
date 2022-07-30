#include <AbstractEntity.h>

namespace DogGE{
    namespace Database{

        AbstractEntity::AbstractEntity(){
            this->id = -1;
        }

        void AbstractEntity::matchIntData(std::string column,int data){
            if(column.compare("id") == 0){
                this->id = data;
            }
        }
        void AbstractEntity::matchInt64Data(std::string column,int64_t data){}
        void AbstractEntity::matchRealData(std::string column,float data){}
        void AbstractEntity::matchStringData(std::string column,std::string data){}
        void AbstractEntity::matchRawData(std::string column,char* data,int length){}
        void AbstractEntity::setEntityRelations(std::string column,AbstractEntity* entity){}
        void AbstractEntity::setEntityArrayRelations(std::string column,std::vector<AbstractEntity*> entities){}

        std::map<std::string,int> AbstractEntity::getIntMap(){
            std::map<std::string,int> ret;
            ret.insert(std::pair<std::string,int>("id",this->getId()));
            return ret;
        }
        std::map<std::string,int64_t> AbstractEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            return ret;
        }
        std::map<std::string,float> AbstractEntity::getRealMap(){
            std::map<std::string,float> ret;
            return ret;
        }
        std::map<std::string,std::string> AbstractEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> AbstractEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            return ret;
        }

        std::map<std::string,std::vector<AbstractEntity*>> AbstractEntity::get1ToNRelations(){}
        std::map<std::string,AbstractEntity*> AbstractEntity::getNTo1Relations(){}

        int AbstractEntity::getId(){
            return this->id;
        }
        void AbstractEntity::setId(int id){
            this->id = id;
        }

    }
}