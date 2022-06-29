#include "TestEntity.h"

int TestEntity::getNumber(){
    return this->number;
}
void TestEntity::setNumber(int number){
    this->number = number;
}
float TestEntity::getReal(){
    return this->real;
}
void TestEntity::setReal(float real){
    this->real = real;
}
std::string TestEntity::getString(){
    return this->string;
}
void TestEntity::setString(std::string string){
    this->string = string;
}
char* TestEntity::getRaw(){
    return this->raw;
}
int TestEntity::getRawSize(){
    return this->rawSize;
}
void TestEntity::setRaw(char* raw,int size){
    this->raw = raw;
    this->rawSize = size;
}

std::string TestEntity::getTableName(){
    return "test";
}
std::string TestEntity::getTableDefinition(){
    return "CREATE TABLE IF NOT EXISTS test("
    "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
    "`number` INTEGER,"
    "`real` REAL,"
    "`string` TEXT,"
    "`raw` BLOB)";
}

void TestEntity::matchIntData(std::string column,int data){
    if(column.compare("number") == 0){
        this->setNumber(data);
    } else {
        DogGE::Database::AbstractEntity::matchIntData(column,data);
    }
}
void TestEntity::matchRealData(std::string column,float data){
    if(column.compare("real") == 0){
        this->setReal(data);
    }
}
void TestEntity::matchStringData(std::string column,std::string data){
    if(column.compare("string") == 0){
        this->setString(data);
    }
}
void TestEntity::matchRawData(std::string column,char* data,int length){
    if(column.compare("raw") == 0){
        this->setRaw(data,length);
    }
}

std::map<std::string,int> TestEntity::getIntMap(){
    std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
    ret.insert(std::pair<std::string,int>("number",this->getNumber()));
    return ret;
}
std::map<std::string,float> TestEntity::getRealMap(){
    std::map<std::string,float> ret;
    ret.insert(std::pair<std::string,float>("real",this->getReal()));
    return ret;
}
std::map<std::string,std::string> TestEntity::getStringMap(){
    std::map<std::string,std::string> ret;
    ret.insert(std::pair<std::string,std::string>("string",this->getString()));
    return ret;
}
std::map<std::string,std::pair<char*,int>> TestEntity::getRawMap(){
    std::map<std::string,std::pair<char*,int>> ret;
    ret.insert( std::pair<std::string,std::pair<char*,int>>("raw",std::pair<char*,int>( this->getRaw(),this->getRawSize() )) );
    return ret;
}