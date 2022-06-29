#include <QueryBuilder.h>
#include <utility>
namespace DogGE{
    namespace Database{
        QueryBuilder::QueryBuilder(Table table){
            this->mFrom = table;
            this->mParameterCount = 0;
            this->mLimit = -1;
            this->mOffset = -1;
        }
        std::string QueryBuilder::buildSql(){
            std::string ret = "SELECT ";
            bool bFirst = true;
            for(auto iter: this->mFrom.columns){
                if(bFirst){
                    bFirst = false;
                } else {
                    ret += ",";
                }
                ret += iter.first;
            }
            ret += " FROM ";
            ret += this->mFrom.tableName;
            ret += " WHERE ";
            bFirst = true;
            for(auto iter: this->mWhere){
                if(bFirst){
                    bFirst = false;
                } else {
                    ret += " AND ";
                }
                ret += iter;
            }

            if(this->mGroupBy.size() > 0){
                ret += " GROUP BY ";
                bool first = true;
                for(auto iter: this->mGroupBy){
                    if(first){
                        first = false;
                    } else {
                        ret += ",";
                    }
                    ret += iter;
                }
            }

            if(this->mOrderBy.size() > 0){
                ret += " ORDER BY ";
                bool first = true;
                for(auto iter:this->mOrderBy){
                    if(first){
                        first = false;
                    } else {
                        ret += ",";
                    }
                    ret += iter.first;
                    if(iter.second){
                        ret += " DESC";
                    }
                }
            }
            

            int limit = this->mLimit;
            int offset = this->mOffset;
            if(limit != -1){
                ret += " LIMIT ";
                ret += std::to_string(limit);
                if(offset != -1){
                    ret += "OFFSET ";
                    ret += std::to_string(offset);
                }
                
            }

            return ret;
        }
        std::string QueryBuilder::buildCountSql(){
            std::string ret = "SELECT COUNT(*) FROM ";
            ret += this->mFrom.tableName;
            ret += " WHERE ";
            bool bFirst = true;
            for(auto iter: this->mWhere){
                if(bFirst){
                    bFirst = false;
                } else {
                    ret += " AND ";
                }
                ret += iter;
            }
            int limit = this->mLimit;
            int offset = this->mOffset;
            if(limit != -1){
                ret += " LIMIT ";
                ret += std::to_string(limit);
                if(offset != -1){
                    ret += " OFFSET ";
                    ret += std::to_string(offset);
                }
                
            }
            
            return ret;
        }
        
        QueryBuilder* QueryBuilder::where(std::string where){
            this->mWhere.push_back(where);
            return this;
        }
        QueryBuilder* QueryBuilder::addIntParameter(int position,int data){
            this->mIntParameter.insert(std::pair<int,int>(position,data));
            this->mParameterCount++;
            return this;
        }
        QueryBuilder* QueryBuilder::addInt64Parameter(int position,int64_t data){
            this->mIntParameter.insert(std::pair<int,int64_t>(position,data));
            this->mParameterCount++;
            return this;
        }
        QueryBuilder* QueryBuilder::addRealParameter(int position,float data){
            this->mRealParameter.insert(std::pair<int,float>(position,data));
            this->mParameterCount++;
            return this;
        }
        QueryBuilder* QueryBuilder::addTextParameter(int position,std::string data){
            this->mTextParameter.insert(std::pair<int,std::string>(position,data));
            this->mParameterCount++;
            return this;
        }
        QueryBuilder* QueryBuilder::addRawParameter(int position,char* data,int length){
            this->mRawParameter.insert(std::pair<int,std::pair<char*,int>>(position,std::pair<char*,int>(data,length)));
            this->mParameterCount++;
            return this;
        }
        QueryBuilder* QueryBuilder::setLimit(int limit,int offset){
            int mLimit = limit;
            int mOffset = offset;
            return this;
        }
        QueryBuilder* QueryBuilder::addOrderBy(std::string field,bool descending){
            this->mOrderBy.push_back(std::pair<std::string,bool>(field,descending));
            return this;
        }
        QueryBuilder* QueryBuilder::addGroupBy(std::string field){
            this->mGroupBy.push_back(field);
            return this;
        }
        std::map<int,int> QueryBuilder::getIntParameters(){
            return this->mIntParameter;
        }
        std::map<int,int64_t> QueryBuilder::getInt64Parameters(){
            return this->mInt64Parameter;
        }
        std::map<int,float> QueryBuilder::getRealParameters(){
            return this->mRealParameter;
        }
        std::map<int,std::string> QueryBuilder::getTextParameters(){
            return this->mTextParameter;
        }
        std::map<int,std::pair<char*,int>> QueryBuilder::getRawParameters(){
            return this->mRawParameter;
        }
        int QueryBuilder::getParameterCount(){
            return this->mParameterCount;
        }
        int QueryBuilder::getLimit(){
            return this->mLimit;
        }
        int QueryBuilder::getOffset(){
            return this->mOffset;
        }
    }
}