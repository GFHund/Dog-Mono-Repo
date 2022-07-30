#include <ArrayTree.h>

namespace DogGE{
    namespace Tree{
        template<class T>
        ArrayTree<T>::ArrayTree()
        {
            mTree = std::vector<ArrayTree<T>*>(1,nullptr);
        }
    }
}


