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

#include <DataClass/LobbyInfoPackage.h>

namespace DogGE{
    namespace F1_2022{
        Header LobbyInfoPackage::getHeader(){return this->header;}
uint8_t LobbyInfoPackage::getNumPlayers(){return this->numPlayers;}
LobbyInfoData* LobbyInfoPackage::getLobbyInfo(){return this->lobbyInfo;}

        void LobbyInfoPackage::setHeader(Header header){this->header = header;}
void LobbyInfoPackage::setNumPlayers(uint8_t numPlayers){this->numPlayers = numPlayers;}
void LobbyInfoPackage::setLobbyInfo(LobbyInfoData* lobbyInfo){for(int i=0;i<22;i++){
this->lobbyInfo[i] = lobbyInfo[i];
}
}

    }
}                    