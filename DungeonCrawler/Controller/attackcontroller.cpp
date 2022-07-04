#include "attackcontroller.h"

// ************************ setter - methods ******************************************
void AttackController::setCharacter(Character *newCharacter){
    character = newCharacter;
}

// ************************ other methods *********************************************
int AttackController::move(){
    std::vector<Tile*> path = level->getPath(this->character->getTile(), level->getCharacters()[0]->getTile());
    bool isPortal = false;

    if(path.size() != 0){
        size_t last = path.size() -1;                                                   // path is in opposite direction in vector -> last element = first Tile to move On
        int portalRow = -1;
        int portalCol = -1;

        for(size_t i = 0; i < level->getPortals().size(); i++){                         // in neighborhood is the destination of the portal stored
            if( path[last] == level->getPortals()[i] ){
                isPortal = true;
                portalRow = level->getPortals()[i]->getDestination()->getRow();         // -> compare with origin portal = destination of destination
                portalCol = level->getPortals()[i]->getDestination()->getColumn();
            }
        }

        int r;
        int c;
        if( isPortal ){                                                                 // calculate distance between thisTile and DestTile (first of path)
            r = portalRow - character->getTile()->getRow();
            c = portalCol - character->getTile()->getColumn();
        } else{
            r =  path[last]->getRow() - character->getTile()->getRow();
            c =  path[last]->getColumn() - character->getTile()->getColumn();
        }

        if( r == 1 && c == -1 ){                                                        // convert to "normal" move-direction (lastInput) for later switch
            return 1;
        } else if( r ==  1 && c ==  0 ){
            return 2;
        } else if( r ==  1 && c ==  1 ){
            return 3;
        } else if( r ==  0 && c == -1 ){
            return 4;
        } else if( r ==  0 && c ==  1 ){
            return 6;
        } else if( r == -1 && c == -1 ){
            return 7;
        } else if( r == -1 && c ==  0 ){
            return 8;
        } else if( r == -1 && c ==  1 ){
            return 9;
        } else {                            // r == 0 && c == 0
            return 5;
        }
    }
    return 5;
}
