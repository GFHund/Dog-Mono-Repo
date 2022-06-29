#include <Generators/GenerateCMakeList.h>
namespace DogGE{
    namespace F1GameParserGenerator{
        void GenerateCMakeList::generateCMakeList(F1Spec spec,std::string outputFolder,std::vector<std::string> sourceFiles){
            kainjow::mustache::data cMakeListData;
            std::string cMakeListSources = "";
            for(auto iter: sourceFiles){
                cMakeListSources += iter;
                cMakeListSources += "\n";
            }
            cMakeListData.set("GAME_NAME",spec.getName());
            cMakeListData.set("SOURCES",cMakeListSources);
            std::string cmakeFile = outputFolder + "/CMakeLists.txt";
            this->renderFile("template/CMakeListsTemplate.txt",cmakeFile,cMakeListData);
        }
    }
}