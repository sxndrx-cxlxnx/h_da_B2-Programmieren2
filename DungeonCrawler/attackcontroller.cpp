#include "attackcontroller.h"

// ************************ setter - methods ******************************************
void AttackController::setCharacter(Character *newCharacter){
    character = newCharacter;
}

// ************************ other methods *********************************************
int AttackController::move(){
    std::vector<Tile*> vec = level->getPath(this->character->getTile(), level->getCharacters()[0]->getTile());
    bool isPortal = false;

    if(vec.size() != 0){
        size_t last = vec.size() -1;
        int portalRow = -1;
        int portalCol = -1;

        for(int i = 0; i < level->getPortals().size(); i++){
            if( vec[last] == level->getPortals()[i] ){
                isPortal = true;
                portalRow = level->getPortals()[i]->getDestination()->getRow();
                portalCol = level->getPortals()[i]->getDestination()->getColumn();
            }
        }
        int r;
        int c;
        if( isPortal ){
            r = portalRow - character->getTile()->getRow();
            c = portalCol - character->getTile()->getColumn();
        }else{
            r =  vec[last]->getRow() - character->getTile()->getRow();
            c =  vec[last]->getColumn() - character->getTile()->getColumn();
        }

        if( r == 1 && c == -1 ){
            return 1;
        } else if( r == 1 && c == 0 ){
            return 2;
        } else if( r == 1 && c == 1 ){
            return 3;
        } else if( r == 0 && c == -1 ){
            return 4;
        } else if( r == 0 && c == 1 ){
            return 6;
        } else if( r == -1 && c == -1 ){
            return 7;
        } else if( r == -1 && c == 0 ){
            return 8;
        } else if( r == -1 && c == 1 ){
            return 9;
        } else {                            // r == 0 && c == 0
            return 5;
        }
    }
    return 5;
}
