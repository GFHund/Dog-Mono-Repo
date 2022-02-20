#include <Exceptions/StateNotFoundException.h>

namespace DogGE{
    namespace StateMachine{
        StateNotFoundException::StateNotFoundException(int id){
            this->mId = id;
            mMessage = "State with id ";
            mMessage += std::to_string(this->mId);
            mMessage += " not found";
        }
        const char* StateNotFoundException::what() const throw(){
            return this->mMessage.c_str();
        }
    }
}

