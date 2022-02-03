#ifndef __DATA_BAG__
#define __DATA_BAG__

namespace DogGE{
    namespace Tree{
        template<class T>
        class DataBag{
            protected:
            T mData;
            public:
            DataBag(T data);
            T getData();
        };
        template<class T>
        DataBag<T>::DataBag(T data){
            this->mData = data;
        }

        template<class T>
        T DataBag<T>::getData(){
            return this->mData;
        }
    }
}

#endif