#include <JsonParser.h>
#include <StateMachine.h>
namespace DogGE{
    namespace Json{
        DogGE::Tree::ArrayTree<AbstractType*> JsonParser::parse(std::string jsonString){

            DogGE::StateMachine::StateMachine<char> sm;
            return DogGE::Tree::ArrayTree<AbstractType*>();
        }
    }
}