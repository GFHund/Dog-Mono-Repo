#include <AbstractEntity.h>

#include <string>
class TestEntity:public DogGE::Database::AbstractEntity{
    private:
    int number;
    float real;
    std::string string;
    char* raw;
    int rawSize;
    public:
    int getNumber();
    void setNumber(int number);
    float getReal();
    void setReal(float real);
    std::string getString();
    void setString(std::string string);
    char* getRaw();
    void setRaw(char* raw,int size);
    int getRawSize();
    

    std::string getTableName() override;
    std::string getTableDefinition() override;
    
    void matchIntData(std::string column,int data) override;
    void matchRealData(std::string column,float data) override;
    void matchStringData(std::string column,std::string data) override;
    void matchRawData(std::string column,char* data,int length) override;

    std::map<std::string,int> getIntMap() override;
    std::map<std::string,float> getRealMap() override;
    std::map<std::string,std::string> getStringMap() override;
    std::map<std::string,std::pair<char*,int>> getRawMap() override;
};