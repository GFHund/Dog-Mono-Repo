#ifndef __QUERY_BUILDER__
#define __QUERY_BUILDER__

#include <Table.h>
#include <string>
#include <vector>
#include <map>

namespace DogGE{
    namespace Database{
        class QueryBuilder{
            private:
            Table mFrom;
            std::vector<std::string> mWhere;
            std::map<int,int> mIntParameter;
            std::map<int,int64_t> mInt64Parameter;
            std::map<int,float> mRealParameter;
            std::map<int,std::string> mTextParameter;
            std::map<int,std::pair<char*,int>> mRawParameter;
            std::vector<std::pair<std::string,bool>> mOrderBy;
            std::vector<std::string> mGroupBy;
            int mParameterCount;
            int mLimit;
            int mOffset;
            public:
            QueryBuilder(Table table);
            std::string buildSql();
            std::string buildCountSql();

            //QueryBuilder* leftJoin();
            QueryBuilder* where(std::string where);
            QueryBuilder* addIntParameter(int position,int data);
            QueryBuilder* addInt64Parameter(int position,int64_t data);
            QueryBuilder* addRealParameter(int position,float data);
            QueryBuilder* addTextParameter(int position,std::string data);
            QueryBuilder* addRawParameter(int position,char* data,int length);
            QueryBuilder* setLimit(int limit,int offset = -1);
            QueryBuilder* addOrderBy(std::string field,bool descending = false);
            QueryBuilder* addGroupBy(std::string field);

            std::map<int,int> getIntParameters();
            std::map<int,int64_t> getInt64Parameters();
            std::map<int,float> getRealParameters();
            std::map<int,std::string> getTextParameters();
            std::map<int,std::pair<char*,int>> getRawParameters();
            int getParameterCount();
            int getLimit();
            int getOffset();
        };
    }
}

#endif