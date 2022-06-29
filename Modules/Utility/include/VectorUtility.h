#ifndef __VECTOR_UTILITY__
#define __VECTOR_UTILITY__
#pragma once

#include <vector>

namespace DogGE{
    namespace Utility{
        template<typename T>
        class VectorUtility{
            private:
            std::vector<T> mArr;
            public:
            VectorUtility(std::vector<T> arr1);

            void setArray(std::vector<T> arr);
            std::vector<T> getArray();
            
            std::vector<T> merge(std::vector<T> arr2);
        };

        template<typename T>
        VectorUtility<T>::VectorUtility(std::vector<T> arr1){
            mArr = arr1;
        }

        template<typename T>
        void VectorUtility<T>::setArray(std::vector<T> arr){
            this->mArr = arr;
        }
        template<typename T>
        std::vector<T> VectorUtility<T>::getArray(){
            return this->mArr;
        }

        template<typename T>
        std::vector<T> VectorUtility<T>::merge(std::vector<T> arr2){
            std::vector<T> ret;
            for(auto iter:mArr){
                ret.push_back(iter);
            }
            for(auto iter:arr2){
                ret.push_back(iter);
            }
            return ret;
        }
    }
}
#endif