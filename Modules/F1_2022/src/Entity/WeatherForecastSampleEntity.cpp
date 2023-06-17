
/**
 * @file F1DataClassTemplate.cpp
 * @author Philipp Holzmann (Philipp1990@web.de)
 * @brief 
 * @version 1.0
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * This file ist generated by the f1GameParserGenerator Program. Any changes will be overriden.
 * 
 */

#include <Entity/WeatherForecastSampleEntity.h>

#include <Exceptions/ValidationException.h>


namespace DogGE{
    namespace F1_2022{
        WeatherForecastSampleEntity::WeatherForecastSampleEntity(){}
WeatherForecastSampleEntity::WeatherForecastSampleEntity(char* rawData,int size,int offset){
this->setSessionType(*((uint8_t*)(rawData+0)));
this->setTimeOffset(*((uint8_t*)(rawData+1)));
this->setWeather(*((uint8_t*)(rawData+2)));
this->setTrackTemperature(*((int8_t*)(rawData+3)));
this->setTrackTemperatureChange(*((int8_t*)(rawData+4)));
this->setAirTemperature(*((int8_t*)(rawData+5)));
this->setAirTemperatureChange(*((int8_t*)(rawData+6)));
this->setRainPercentage(*((uint8_t*)(rawData+7)));
}

        uint8_t WeatherForecastSampleEntity::getSessionType(){return this->sessionType;}
uint8_t WeatherForecastSampleEntity::getTimeOffset(){return this->timeOffset;}
uint8_t WeatherForecastSampleEntity::getWeather(){return this->weather;}
int8_t WeatherForecastSampleEntity::getTrackTemperature(){return this->trackTemperature;}
int8_t WeatherForecastSampleEntity::getTrackTemperatureChange(){return this->trackTemperatureChange;}
int8_t WeatherForecastSampleEntity::getAirTemperature(){return this->airTemperature;}
int8_t WeatherForecastSampleEntity::getAirTemperatureChange(){return this->airTemperatureChange;}
uint8_t WeatherForecastSampleEntity::getRainPercentage(){return this->rainPercentage;}

        void WeatherForecastSampleEntity::setSessionType(uint8_t sessionType){this->sessionType = sessionType;}
void WeatherForecastSampleEntity::setTimeOffset(uint8_t timeOffset){this->timeOffset = timeOffset;}
void WeatherForecastSampleEntity::setWeather(uint8_t weather){this->weather = weather;}
void WeatherForecastSampleEntity::setTrackTemperature(int8_t trackTemperature){this->trackTemperature = trackTemperature;}
void WeatherForecastSampleEntity::setTrackTemperatureChange(int8_t trackTemperatureChange){this->trackTemperatureChange = trackTemperatureChange;}
void WeatherForecastSampleEntity::setAirTemperature(int8_t airTemperature){this->airTemperature = airTemperature;}
void WeatherForecastSampleEntity::setAirTemperatureChange(int8_t airTemperatureChange){this->airTemperatureChange = airTemperatureChange;}
void WeatherForecastSampleEntity::setRainPercentage(uint8_t rainPercentage){this->rainPercentage = rainPercentage;}


        std::string WeatherForecastSampleEntity::getTableName(){
            return "WeatherForecastSampleEntity";
        }
        std::string WeatherForecastSampleEntity::getTableDefinition(){
            return "CREATE TABLE IF NOT EXISTS WeatherForecastSampleEntity("
            "`id` INTEGER PRIMARY KEY AUTOINCREMENT,`sessionType` INTEGER,`timeOffset` INTEGER,`weather` INTEGER,`trackTemperature` INTEGER,`trackTemperatureChange` INTEGER,`airTemperature` INTEGER,`airTemperatureChange` INTEGER,`rainPercentage` INTEGER)";
        }
        
        void WeatherForecastSampleEntity::matchIntData(std::string column,int data){
            if(column.compare("trackTemperature") == 0){
this->setTrackTemperature(data);
} else if(column.compare("trackTemperatureChange") == 0){
this->setTrackTemperatureChange(data);
} else if(column.compare("airTemperature") == 0){
this->setAirTemperature(data);
} else if(column.compare("airTemperatureChange") == 0){
this->setAirTemperatureChange(data);
} else {DogGE::Database::AbstractEntity::matchIntData(column,data);}

        }
        void WeatherForecastSampleEntity::matchInt64Data(std::string column,int64_t data){
            
        }
        void WeatherForecastSampleEntity::matchRealData(std::string column,float data){
            
        }
        void WeatherForecastSampleEntity::matchStringData(std::string column,std::string data){}
        void WeatherForecastSampleEntity::matchRawData(std::string column,char* data,int length){
            
        }

        std::map<std::string,int> WeatherForecastSampleEntity::getIntMap(){
            std::map<std::string,int> ret = DogGE::Database::AbstractEntity::getIntMap();
            ret.insert(std::pair<std::string,int>("trackTemperature",this->getTrackTemperature()));
ret.insert(std::pair<std::string,int>("trackTemperatureChange",this->getTrackTemperatureChange()));
ret.insert(std::pair<std::string,int>("airTemperature",this->getAirTemperature()));
ret.insert(std::pair<std::string,int>("airTemperatureChange",this->getAirTemperatureChange()));

            return ret;
        }
        std::map<std::string,int64_t> WeatherForecastSampleEntity::getInt64Map(){
            std::map<std::string,int64_t> ret;
            
            return ret;
        }
        std::map<std::string,float> WeatherForecastSampleEntity::getRealMap(){
            std::map<std::string,float> ret;
            
            return ret;
        }
        std::map<std::string,std::string> WeatherForecastSampleEntity::getStringMap(){
            std::map<std::string,std::string> ret;
            return ret;
        }
        std::map<std::string,std::pair<char*,int>> WeatherForecastSampleEntity::getRawMap(){
            std::map<std::string,std::pair<char*,int>> ret;
            
            return ret;
        }
    }
}                                                                        